#include <gtest/gtest.h>
#include "../../src/SVGShapesManager.h"
#include "../../src/shared/Point2D.h"

const char* MOCK_FILE_CONTENT = "1. rect 5 5 10 10 green\n2. circle 5 5 5 blue\n3. rect 100 60 10 10 red\n4. rect 1 1 30 30 yellow\n5. circle 0 0 1 yellow\n";

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(AC_test, Given_open_app_When_print_command_is_chosen_Then_all_the_figures_are_printed)
{
    // Arrange
    SVGShapesManager currentManager;
    currentManager.loadSVGFile("tests/acceptance_tests/test_figures.svg");

    testing::internal::CaptureStdout();

    // Act
    currentManager.printShapes();

    // Assert
    ASSERT_STREQ(MOCK_FILE_CONTENT, testing::internal::GetCapturedStdout().c_str());
}

TEST(AC_test, Given_open_app_When_create_new_figure_is_chosen_Then_the_new_figure_is_added)
{
    // Arrange
    SVGShapesManager currentManager;
    Vector<Attribute> shapeAttributes;
    shapeAttributes.push_back(Attribute("circle", "", false));
    shapeAttributes.push_back(Attribute("cx", "10", true));
    shapeAttributes.push_back(Attribute("cy", "10", true));
    shapeAttributes.push_back(Attribute("r", "10", true));
    shapeAttributes.push_back(Attribute("fill", "yellow", false));
    Shape* newShape = new Circle(shapeAttributes);

    char expectedShape[] = "1. circle 10 10 10 yellow\n";

    testing::internal::CaptureStdout();

    // Act
    currentManager.addShape(newShape);
    currentManager.printShapes();

    // Assert
    ASSERT_STREQ(expectedShape, testing::internal::GetCapturedStdout().c_str());

    delete newShape;
}

TEST(AC_test, Given_open_app_When_translate_one_figure_is_chosen_Then_the_figure_is_translated)
{
    // Arrange
    SVGShapesManager currentManager;
    currentManager.loadSVGFile("tests/acceptance_tests/test_figures.svg");

    char successMessage[] = "Successfully translated shape at index 2\n";

    char* expectedMessage = new char[strlen(successMessage) + strlen(MOCK_FILE_CONTENT) + 1];
    strcpy(expectedMessage, successMessage);
    strcat(expectedMessage, MOCK_FILE_CONTENT);

    int secondFigureIndex = strstr(expectedMessage, "2. circle ") - expectedMessage;
    ASSERT_GT(secondFigureIndex, -1);
    ASSERT_LT(secondFigureIndex, strlen(expectedMessage));

    int coordinatesStartIndex = secondFigureIndex + strlen("2. circle ");
    strncpy(expectedMessage + coordinatesStartIndex, "8 7", 3);

    testing::internal::CaptureStdout();

    // Act
    currentManager.translateShapes(Point2D(3, 2), 2);
    currentManager.printShapes();

    // Assert
    ASSERT_STREQ(expectedMessage, testing::internal::GetCapturedStdout().c_str());

    delete[] expectedMessage;
}

TEST(AC_test, Given_open_app_When_within_is_chosen_Then_correct_figures_are_printed)
{
    // Arrange
    SVGShapesManager currentManager;
    currentManager.loadSVGFile("tests/acceptance_tests/test_figures.svg");
    Vector<Attribute> shapeAttributes;
    shapeAttributes.push_back(Attribute("circle", "", false));
    shapeAttributes.push_back(Attribute("cx", "10", true));
    shapeAttributes.push_back(Attribute("cy", "10", true));
    shapeAttributes.push_back(Attribute("r", "10", true));
    Circle currentCircle(shapeAttributes);

    char expectedMessage[] = "1. rect 5 5 10 10 green\n";

    testing::internal::CaptureStdout();

    // Act
    currentManager.containedInCircle(currentCircle);

    // Assert
    ASSERT_STREQ(expectedMessage, testing::internal::GetCapturedStdout().c_str());

}