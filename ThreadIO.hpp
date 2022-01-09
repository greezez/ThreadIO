#pragma once
#ifndef THREAD_IO_HPP
#define THREAD_IO_HPP

#include <atomic>

namespace ThreadIO
{

	enum class ErrorCodeList : uint8_t
	{
		Success = 0,
		BadAlloc,
	};


	class ErrorCode
	{
	public:

		ErrorCode() : code(ErrorCodeList::Success)
		{
		}

		~ErrorCode()
		{
		}

	private:

		ErrorCodeList code;

	};


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

			List(size_t size, ErrorCode& ec) : current(nullptr), head(nullptr), tail(nullptr)
			{
			}

			~List()
			{
			}

			T& current() {}

			updateCurrent() {}

			bool addAfterCurrent() {}
			bool deleteAfterCurrent() {}

			void resetCurrent() {}

			template<typename Fn>
			void forEach(Fn fn) {}

		private:

			Node* current;

			Node* head;
			Node* tail;

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



#endif // !THREAD_IO_HPP
