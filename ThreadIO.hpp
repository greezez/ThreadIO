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

			List(size_t size, ErrorCode& ec) : cuurent(nullptr), head(nullptr), tail(nullptr)
			{
			}

			~List()
			{
			}

		private:

			Node* cuurent;

			Node* head;
			Node* tail;

		};


	}



	template <typename T, typename Tg>
	class ThreadIOBase
	{

		using Type = T;
		using TagType = Tg;

	public:

		ThreadIOBase()
		{
		}

		~ThreadIOBase()
		{
		}

	private:

	};



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
