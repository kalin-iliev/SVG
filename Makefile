GCC=g++

all: directories Attribute.o CommonAttributes.o MainAttributes.o String.o Circle.o Line.o Rectangle.o ShapeAsText.o ConsoleHelpers.o InputHandler.o StringHelpers.o Command.o SVGAppWrapper.o SVGShapesManager.o
	$(GCC) -o svg obj/Attribute.o obj/CommonAttributes.o obj/MainAttributes.o obj/String.o obj/Shape.o obj/Circle.o obj/Line.o obj/Rectangle.o obj/ShapeAsText.o obj/ConsoleHelpers.o obj/InputHandler.o obj/StringHelpers.o obj/Command.o obj/SVGAppWrapper.o obj/SVGShapesManager.o src/Main.cpp -Isrc/shared/utils -Isrc/shared -Isrc/shapes -Isrc/containers -Isrc -Isrc/attributes

directories:
	mkdir -p obj

Attribute.o: src/attributes/Attribute.cpp src/attributes/Attribute.h src/containers/String.h src/shared/utils/StringHelpers.h
	$(GCC) -c -o obj/Attribute.o src/attributes/Attribute.cpp -Isrc/containers -Isrc/shared/utils

CommonAttributes.o: src/attributes/CommonAttributes.cpp src/attributes/CommonAttributes.h src/containers/String.h src/shared/utils/StringHelpers.h src/containers/Vector.h src/attributes/Attribute.h src/shared/Constants.h
	$(GCC) -c -o obj/CommonAttributes.o src/attributes/CommonAttributes.cpp -Isrc/containers -Isrc/shared/utils -Isrc/shared

MainAttributes.o: src/attributes/MainAttributes.cpp src/attributes/MainAttributes.h src/containers/String.h src/containers/Vector.h src/attributes/Attribute.h src/attributes/CommonAttributes.h src/shared/utils/StringHelpers.h
	$(GCC) -c -o obj/MainAttributes.o src/attributes/MainAttributes.cpp -Isrc/containers -Isrc/shared/utils -Isrc/shared

String.o: src/containers/String.cpp src/containers/String.h src/shared/utils/StringHelpers.h
	$(GCC) -c -o obj/String.o src/containers/String.cpp -Isrc/containers -Isrc/shared/utils

Shape.o: src/shapes/Shape.h src/shapes/Shape.cpp src/attributes/CommonAttributes.h src/attributes/MainAttributes.h src/containers/Vector.h src/shared/utils/StringHelpers.h src/shared/Constants.h
	$(GCC) -c -o obj/Shape.o src/shapes/Shape.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Circle.o: Shape.o src/shapes/Circle.cpp src/shapes/Circle.h
	$(GCC) -c -o obj/Circle.o src/shapes/Circle.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Line.o: Shape.o src/shapes/Line.cpp src/shapes/Line.h
	$(GCC) -c -o obj/Line.o src/shapes/Line.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

Rectangle.o: Shape.o src/shapes/Rectangle.cpp src/shapes/Rectangle.h
	$(GCC) -c -o obj/Rectangle.o src/shapes/Rectangle.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

ShapeAsText.o: Shape.o src/shapes/ShapeAsText.cpp src/shapes/ShapeAsText.h
	$(GCC) -c -o obj/ShapeAsText.o src/shapes/ShapeAsText.cpp -Isrc/attributes -Isrc/containers -Isrc/shared/utils -Isrc/shared

ConsoleHelpers.o: src/shared/utils/ConsoleHelpers.h src/shared/utils/ConsoleHelpers.cpp src/shared/utils/InputHandler.h src/SVGShapesManager.h src/shared/Command.h
	$(GCC) -c -o obj/ConsoleHelpers.o src/shared/utils/ConsoleHelpers.cpp -Isrc/shared -Isrc/shared/utils -Isrc  -Isrc/shapes -Isrc/attributes -Isrc/containers

InputHandler.o: src/shared/utils/InputHandler.h src/attributes/Attribute.h src/SVGShapesManager.h src/shared/Constants.h
	$(GCC) -c -o obj/InputHandler.o src/shared/utils/InputHandler.cpp -Isrc/shared -Isrc/shared/utils -Isrc  -Isrc/shapes -Isrc/attributes -Isrc/containers

StringHelpers.o: src/shared/utils/StringHelpers.h
	$(GCC) -c -o obj/StringHelpers.o src/shared/utils/StringHelpers.cpp

Command.o: src/shared/Command.h src/containers/String.h src/containers/Vector.h src/shared/utils/StringHelpers.h
	$(GCC) -c -o obj/Command.o src/shared/Command.cpp -Isrc/containers -Isrc/shared/utils

SVGAppWrapper.o: src/SVGAppWrapper.h src/shared/utils/ConsoleHelpers.h
	$(GCC) -c -o obj/SVGAppWrapper.o src/SVGAppWrapper.cpp -Isrc/shared/utils -Isrc/ -Isrc/shapes -Isrc/attributes -Isrc/containers -Isrc/shared

SVGShapesManager.o: src/SVGShapesManager.h src/shapes/Shape.h src/shapes/Line.h src/shapes/Rectangle.h src/shapes/Circle.h src/containers/String.h
	$(GCC) -c -o obj/SVGShapesManager.o src/SVGShapesManager.cpp -Isrc/shapes -Isrc/containers -Isrc/attributes -Isrc/shared -Isrc/shared/utils

tests: tests/acceptance_tests/main.cpp
	$(GCC) -o runTests -Wall -g -pthread tests/acceptance_tests/main.cpp -lgtest -lgtest_main -lpthread

clean:
	rm -f runTests
	rm -rf obj/