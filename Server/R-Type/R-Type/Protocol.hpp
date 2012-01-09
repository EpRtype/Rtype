#ifndef		_PROTOCOL_HPP_
#define		_PROTOCOL_HPP_

#ifdef __linux__
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef int int32_t;
#endif

namespace RTProtocol
{
	#pragma pack(push, 1)

	enum			COMMAND
	{
		CONNECTION = 0,
		RUN_MODE,
		IDENTIFIER,
		GAME_STATE,
		GAME_ACTION
	};

	struct			Header
	{
		uint8_t		Command;
		int32_t		Size;
	};

	enum			CONNECTION
	{
		LOG_IN = 0,
		LOG_OUT
	};

	struct			Connection
	{
		uint8_t		StateConnection;
	};

	enum			RUN_MODE
	{
		CREATE = 0,
		JOIN
	};

	struct			RunMode
	{
		uint8_t		Mode;
	};

	enum			IDENTIFIER
	{
		NO_PLAY = -1,
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4
	};

	struct			Identifier
	{
		uint8_t		Id;
	};

	enum			GAME_STATE
	{
		START = 0,
		END
	};

	struct			GameState
	{
		uint8_t		State;
	};

	enum			GAME_ACTION
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		SHOOT
	};

	struct			GameAction
	{
		uint8_t		Action;
	};

	#pragma pack(pop)

}

#endif		/* PROTOCOLP_HPP */