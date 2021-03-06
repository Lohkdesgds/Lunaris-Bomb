#pragma once

#include <functional>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <mutex>
#include <memory>

// Bomb has debug commented because it's widely used now

namespace Lunaris {

	/// <summary>
	/// <para>bomb is a really good tool when you need something to run then everything is destroyed (when things goes out of scope).</para>
	/// <para>You create the bomb with a function. The function is run when the object is destroyed. Easy, right?</para>
	/// <para>You can defuse the bomb if you don't want the function running at the end, maybe you've set the bomb for exception recovery and if things goes right you defuse it, I don't know.</para>
	/// </summary>
	class bomb {
		mutable std::mutex saf;
		std::function<void(void)> boom;
	public:
		/// <summary>
		/// <para>Arm the bomb (when destroyed, this is triggered, unless it's defused!)</para>
		/// </summary>
		/// <param name="{function}">A function-bomb.</param>
		bomb(const std::function<void(void)>);

		// detonate
		~bomb();

		bomb(const bomb&) = delete;
		void operator=(const bomb&) = delete;

		/// <summary>
		/// <para>Move the BOMB!</para>
		/// </summary>
		/// <param name="{bomb}">The bomb being moved!</param>
		bomb(bomb&&) noexcept;

		/// <summary>
		/// <para>Move the BOMB!</para>
		/// <para>NOTE! If this bomb here has a bomb inside, it'll be triggered! BE CAREFUL!</para>
		/// </summary>
		/// <param name="{bomb}">The bomb being moved!</param>
		void operator=(bomb&&) noexcept;

		/// <summary>
		/// <para>Defuse the bomb! (The function will not be triggered)</para>
		/// </summary>
		/// <returns>The function set, if you want that.</returns>
		std::function<void(void)> defuse();

		/// <summary>
		/// <para>Is this bomb defused?</para>
		/// </summary>
		/// <returns>{bool} Defused?</returns>
		bool is_defused() const;

		/// <summary>
		/// <para>If not defused, it's considered valid.</para>
		/// </summary>
		/// <returns>{bool} is it still valid (not defused)?</returns>
		bool valid() const;

		/// <summary>
		/// <para>If defused, it's considered empty.</para>
		/// </summary>
		/// <returns>{bool} has bomb set?</returns>
		bool empty() const;
	};

	/// <summary>
	/// <para>A timed_bomb should feel like a bomb, but it has a timer trigger too! If timed out or destroyed, BOOM.</para>
	/// </summary>
	class timed_bomb {
		struct _bomb {
			bomb _bmb;
			std::thread _thr;
			_bomb(std::function<void()>);
		};
		std::shared_ptr<_bomb> movable_bomb;
	public:
		/// <summary>
		/// <para>Arm a bomb with a timer! If not defused, it "explodes" when destroyed or when timeout triggers.</para>
		/// </summary>
		/// <param name="{function}">A function-bomb.</param>
		/// <param name="{double}">Delta time in seconds.</param>
		timed_bomb(const std::function<void(void)>, const double);

		// detonate
		~timed_bomb();

		timed_bomb(const timed_bomb&) = delete;
		void operator=(const timed_bomb&) = delete;

		/// <summary>
		/// <para>Move the BOMB!</para>
		/// </summary>
		/// <param name="{bomb}">The bomb being moved!</param>
		timed_bomb(timed_bomb&&) noexcept;

		/// <summary>
		/// <para>Move the BOMB!</para>
		/// <para>NOTE! If this bomb here has a bomb inside, it'll be triggered! BE CAREFUL!</para>
		/// </summary>
		/// <param name="{bomb}">The bomb being moved!</param>
		void operator=(timed_bomb&&) noexcept;

		/// <summary>
		/// <para>Defuse the bomb! (The function will not be triggered)</para>
		/// </summary>
		/// <returns>The function set, if you want that.</returns>
		std::function<void(void)> defuse();

		/// <summary>
		/// <para>Is this bomb defused?</para>
		/// </summary>
		/// <returns>{bool} Defused?</returns>
		bool is_defused() const;

		/// <summary>
		/// <para>If not defused, it's considered valid.</para>
		/// </summary>
		/// <returns>{bool} is it still valid (not defused)?</returns>
		bool valid() const;

		/// <summary>
		/// <para>If defused, it's considered empty.</para>
		/// </summary>
		/// <returns>{bool} has bomb set?</returns>
		bool empty() const;
	};

}

#include "bomb.ipp"