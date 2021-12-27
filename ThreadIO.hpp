#pragma once

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


	class ThreadIO
	{
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