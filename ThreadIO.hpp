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
					if (!push())
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


			bool push() noexcept
			{
				Node* node = createNode();

				if (node == nullptr)
					return false;
			
				node->next = head_;
				head_ = node;

				if (current_ == nullptr)
					current_ = head_;

				size_++;

				return true;
			}


			void pop() noexcept
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


			bool insertAndUpdateCurrent() noexcept
			{
				if (head_ == nullptr)
				{
					if (!push())
						return false;

					current_ = head_;
					return true;
				}

				Node* node = createNode();

				if (node == nullptr)
					return false;

				node->next = current_->next;
				current_->next = node;
				current_ = node;

				size_++;

				return true;
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


			size_t size() noexcept
			{
				return size_;
			}


		private:

			Node* createNode() noexcept
			{
				Node* node = new(std::nothrow) Node;

				if (node == nullptr)
					return nullptr;

				return node;
			}


		private:

			Node* current_;
			Node* head_;

			size_t size_;

		};



		class Data
		{
		public:
			Data(size_t size, bool& success) noexcept : 
				data_(nullptr), size_(size), offset_(0), numOfAcquired_(0)
			{
			}

			~Data()
			{
			}

			void* acquire(size_t size) noexcept
			{
			}

			void release() 
			{}

			size_t numOfAcquired()
			{}

			const void* get()
			{}

		private:

			void* data_;
			size_t size_;
			size_t offset_;

			std::atomic_size_t numOfAcquired_;

		};



		class DataPool
		{
		public:
			DataPool()
			{
			}

			~DataPool()
			{
			}

		private:

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
