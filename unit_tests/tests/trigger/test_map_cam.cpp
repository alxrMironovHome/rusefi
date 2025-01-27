

#include "pch.h"
#include "trigger_central.h"

TEST(trigger, map_cam_by_magic_point) {

	EngineTestHelper eth(TEST_CRANK_ENGINE);

	engineConfiguration->camInputs[0] = GPIOA_0;
	engineConfiguration->vvtMode[0] = VVT_MAP_V_TWIN_ANOTHER;

	engine->outputChannels.instantMAPValue = 100;

	engineConfiguration->mapCamDetectionAnglePosition = 90;

	eth.smartFireTriggerEvents2(/*count*/10, /*delayMs*/200);
	ASSERT_EQ( 75,  GET_RPM()) << "RPM";

	ASSERT_EQ(1, engine->outputChannels.TEMPLOG_map_peak);
	ASSERT_EQ(0, engine->outputChannels.vvtSyncCounter);


	engine->outputChannels.instantMAPValue = 120;
	eth.smartFireTriggerEvents2(/*count*/4, /*delayMs*/200);

	ASSERT_EQ(2, engine->outputChannels.TEMPLOG_map_peak);
	ASSERT_EQ(1, engine->outputChannels.vvtSyncCounter);
	ASSERT_EQ(6, engine->outputChannels.TEMPLOG_MAP_AT_CYCLE_COUNT);

}
