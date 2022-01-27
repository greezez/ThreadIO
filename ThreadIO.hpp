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

			UniqueData()
			{
			}

			~UniqueData()
			{
			}

		private:

		};


		class DataPool
		{

		public:

			DataPool(size_t dataSize, size_t poolSize, bool& success) noexcept :
				dataSize_(dataSize), dataList_(poolSize, success)
			{

			}

			~DataPool()
			{
			}

			bool tryAcquire() noexcept {}
			bool acquire() noexcept {}

			bool tryHeapAcquire() noexcept {}

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
