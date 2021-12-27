#pragma once
#ifndef THREAD_IO_HPP
#define THREAD_IO_HPP

#include <atomic>

namespace ThreadIO
{

	namespace details
	{

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
