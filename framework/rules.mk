PIRIS_FRAMEWORK := $(PIRIS)
CPPFILES +=  $(wildcard $(PIRIS_FRAMEWORK)/*.cpp) $(PIRIS_FRAMEWORK)/utils/touch_calibration.cpp
INCDIR += $(PIRIS_FRAMEWORK) $(PIRIS_FRAMEWORK)/utils
