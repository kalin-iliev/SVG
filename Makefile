GCC=g++
ALL_O_FILES=obj/Attribute.o obj/AttributesContainer.o obj/String.o obj/Shape.o obj/Line.o obj/Circle.o obj/Rectangle.o obj/ConsoleHelpers.o obj/Helpers.o obj/InputHandler.o obj/Command.o obj/SVGAppWrapper.o obj/SVGShapesManager.o
ALL_HEADER_FILES=-Isrc/shared/utils -Isrc/shared -Isrc/shapes -Isrc/containers -Isrc -Isrc/attributes

all: directories Attribute.o AttributesContainer.o String.o Circle.o Line.o Rectangle.o ConsoleHelpers.o Helpers.o InputHandler.o Command.o SVGAppWrapper.o SVGShapesManager.o
	$(GCC) -o svg src/Main.cpp $(ALL_O_FILES) $(ALL_HEADER_FILES) 

directories:
	mkdir -p obj

Helpers.o: src/shared/utils/Helpers.h src/shared/utils/Helpers.cpp
	$(GCC) -c -o obj/Helpers.o src/shared/utils/Helpers.cpp -Isrc/utils -Isrc/containers

Attribute.o: src/attributes/Attribute.cpp src/attributes/Attribute.h src/containers/String.h
	$(GCC) -c -o obj/Attribute.o src/attributes/Attribute.cpp -Isrc/containers -Isrc/shared/utils

AttributesContainer.o: src/attributes/AttributesContainer.cpp src/attributes/AttributesContainer.h src/containers/String.h src/containers/Vector.h src/attributes/Attribute.h src/shared/Constants.h
	$(GCC) -c -o obj/AttributesContainer.o src/attributes/AttributesContainer.cpp -Isrc/containers -Isrc/shared/utils -Isrc/shared

String.o: src/containers/String.cpp src/containers/String.h
	$(GCC) -c -o obj/String.o src/containers/String.cpp -Isrc/containers -Isrc/shared/utils

Shape.o: src/shapes/Shape.h src/shapes/Shape.cpp src/attributes/AttributesContainer.h src/containers/Vector.h src/shared/Constants.h
	$(GCC) -c -o obj/Shape.o src/shapes/Shape.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Circle.o: Shape.o src/shapes/Circle.cpp src/shapes/Circle.h
	$(GCC) -c -o obj/Circle.o src/shapes/Circle.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Line.o: Shape.o src/shapes/Line.cpp src/shapes/Line.h
	$(GCC) -c -o obj/Line.o src/shapes/Line.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Rectangle.o: Shape.o src/shapes/Rectangle.cpp src/shapes/Rectangle.h
	$(GCC) -c -o obj/Rectangle.o src/shapes/Rectangle.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

ConsoleHelpers.o: src/shared/utils/ConsoleHelpers.h src/shared/utils/ConsoleHelpers.cpp src/shared/utils/InputHandler.h src/SVGShapesManager.h src/shared/Command.h
	$(GCC) -c -o obj/ConsoleHelpers.o src/shared/utils/ConsoleHelpers.cpp -Isrc/shared -Isrc/shared/utils -Isrc  -Isrc/shapes -Isrc/attributes -Isrc/containers

InputHandler.o: src/shared/utils/InputHandler.h src/attributes/Attribute.h src/SVGShapesManager.h src/shared/Constants.h
	$(GCC) -c -o obj/InputHandler.o src/shared/utils/InputHandler.cpp -Isrc/shared -Isrc/shared/utils -Isrc  -Isrc/shapes -Isrc/attributes -Isrc/containers

Command.o: src/shared/Command.h src/containers/String.h src/containers/Vector.h
	$(GCC) -c -o obj/Command.o src/shared/Command.cpp -Isrc/containers -Isrc/shared/utils

SVGAppWrapper.o: src/SVGAppWrapper.h src/shared/utils/ConsoleHelpers.h
	$(GCC) -c -o obj/SVGAppWrapper.o src/SVGAppWrapper.cpp -Isrc/shared/utils -Isrc/ -Isrc/shapes -Isrc/attributes -Isrc/containers -Isrc/shared

SVGShapesManager.o: src/SVGShapesManager.h src/shapes/Shape.h src/shapes/Line.h src/shapes/Rectangle.h src/shapes/Circle.h src/containers/String.h
	$(GCC) -c -o obj/SVGShapesManager.o src/SVGShapesManager.cpp -Isrc/shapes -Isrc/containers -Isrc/attributes -Isrc/shared -Isrc/shared/utils

tests: tests/acceptance_tests/main.cpp
	$(GCC) -o runTests -Wall -g -pthread tests/acceptance_tests/main.cpp $(ALL_O_FILES) -lgtest -lgtest_main -lpthread $(ALL_HEADER_FILES)

clean:
	rm -f runTests
	rm -rf obj/