#pragma once
#ifndef THREAD_IO_GREEZEZ_HPP
#define THREAD_IO_GREEZEZ_HPP

#include <atomic>

namespace ThreadIO
{

	namespace details
	{

		template<typename T>
		class List
		{

			struct Node
			{
				Node* next{nullptr};
				T item{};
			};

		public:

			List(size_t size, bool& success) noexcept : 
				current_(nullptr), head_(nullptr), size_(0)
			{
				for (size_t i = 0; i < size; i++)
				{
					if (!pushFront())
					{
						clear();
						success = false;
						return;
					}
				}

				current_ = head_;
				success = true;
			}

			List() noexcept :
				current_(nullptr), head_(nullptr), size_(0)
			{}


			~List()
			{
				clear();
			}


			T& current() 
			{
				return current_->item;
			}

			T& front()
			{
				return head_->item;
			}


			bool pushFront() noexcept
			{
				Node* node = new(std::nothrow) Node;

				if (node == nullptr)
					return false;
			
				node->next = head_;
				head_ = node;

				if (current_ == nullptr)
					current_ = head_;

				size_++;

				return true;
			}


			void popFront() noexcept
			{
				if (head_ == nullptr)
					return;

				Node* node = head_;
				head_ = node->next;

				size_--;

				delete node;
			}


			void updateCurrent() noexcept
			{
				if (current_->next != nullptr)
				{
					current_ = current_->next;
					return;
				}

				current_ = head_;
			}


			T* insertAndUpdateCurrent() noexcept
			{
				if (head_ == nullptr)
				{
					if (pushFront())
						return &current_->item;

					return nullptr;
				}

				Node* node = new(std::nothrow) Node;

				if (node == nullptr)
					return nullptr;

				node->next = current_->next;
				current_->next = node;
				current_ = node->next;

				size_++;

				return &node->item;
			}


			void clear() noexcept
			{
				Node* node = nullptr;

				while (head_ != nullptr)
				{
					node = head_;
					head_ = head_->next;

					delete node;
				}

				size_ = 0;
				current_ = nullptr;
			}


			void resetCurrent()
			{
				current_ = head_;
			}

			template<typename Fn>
			void forEach(Fn fn)
			{
				Node* node = head_;

				while (node != nullptr)
				{
					fn(node->item);

					node = node->next;
				}
			}


			size_t size() noexcept
			{
				return size_;
			}


		private:

			Node* current_;
			Node* head_;

			size_t size_;

		};


		struct Data
		{

			Data() noexcept : data(nullptr), offset(0), numOfAcqured(0)
			{}

			void* data;
			size_t offset;
			std::atomic_size_t numOfAcqured;

		};
		

		class DataPool;


		class UniqueData
		{

			friend class DataPool;

		public:

			UniqueData() noexcept : 
				data_(nullptr), numOfAcquired_(nullptr), isHeap_(false)
			{}


			UniqueData(const UniqueData& other) = delete;
			UniqueData& operator=(const UniqueData& other) = delete;


			UniqueData(UniqueData&& other) noexcept :
				data_(other.data_), numOfAcquired_(other.numOfAcquired_), isHeap_(other.isHeap_)
			{
				other.data_ = nullptr;
				other.numOfAcquired_ = nullptr;
				other.isHeap_ = false;
			}


			UniqueData& operator=(UniqueData&& other) noexcept
			{
				data_ = other.data_;
				numOfAcquired_ = other.numOfAcquired_;
				isHeap_ = other.isHeap_;

				other.data_ = nullptr;
				other.numOfAcquired_ = nullptr;
				other.isHeap_ = false;

				return *this;
			}


			~UniqueData()
			{
				release();
			}


			void* get() noexcept
			{
				return data_;
			}


			void release() noexcept
			{
				if (!isValid())
					return;

				if (isHeap_)
					std::free(data_);
				else
					numOfAcquired_->fetch_sub(1, std::memory_order_release);

				data_ = nullptr;
				numOfAcquired_ = nullptr;
			}


			bool isValid()
			{
				if (isHeap_)
					return data_ != nullptr;

				return data_ != nullptr and numOfAcquired_ != nullptr;
			}


		private:

			void set(void* data, std::atomic_size_t* numOfAcquired, bool isHeap = false) noexcept
			{
				data_ = data;
				numOfAcquired_ = numOfAcquired;
				isHeap_ = isHeap;
			}


		private:

			void* data_;
			std::atomic_size_t* numOfAcquired_;
			bool isHeap_;

		};


		class DataPool
		{

		public:

			DataPool(size_t dataSize, size_t poolSize, bool& success) noexcept :
				dataSize_(dataSize), dataList_()
			{
				for (size_t i = 0; i < poolSize; i++)
				{
					if (dataList_.pushFront())
					{
						void* data = std::malloc(dataSize);

						if (data == nullptr)
						{
							clear();
							success = false;
							return;
						}

						dataList_.front().data = data;
					}
				}

				dataList_.resetCurrent();
				success = true;
			}

			~DataPool()
			{
				clear();
			}

			bool tryAcquire(UniqueData& data, size_t size) noexcept 
			{}


			bool acquire(UniqueData& data, size_t size) noexcept 
			{}


			bool tryHeapAcquire(UniqueData& uniqueData, size_t size) noexcept
			{
				void* data = std::malloc(size);

				if (data == nullptr)
					return false;

				uniqueData.set(data, nullptr, true);
				return true;
			}

			//del
			void info()
			{
				dataList_.forEach(
					[](const Data& dt) 
					{
						std::cout << "offset: " << dt.offset << " NOA: " << dt.numOfAcqured.load(std::memory_order_acquire) << std::endl;
					});
			}

			void clear()
			{
				dataList_.forEach(
					[](Data& data) 
					{ 
						std::free(data.data); 
					});

				dataList_.clear();
			}

			size_t size()
			{
				return dataList_.size();
			}

		private:

			size_t dataSize_;
			List<Data> dataList_;
			
		};

	}



	template<typename Tg>
	class ThreadIO
	{

		using TagType = Tg;


	public:

		ThreadIO()
		{
		}

		~ThreadIO()
		{
		}


	private:

	};


}



#endif // !THREAD_IO_GREEZEZ_HPP
