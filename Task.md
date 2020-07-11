# Проект: Работа със SVG файлове

В рамките на този проект трябва да се разработи приложение, което работи със файлове във Scalable Vector Graphics (SVG) формат. Приложението трябва да може да зарежда фигури от файла, да извършва върху тях дадени операции, след което да може да записва промените обратно на диска.

За улеснение, в рамките на проекта ще работим само с основните фигури (basic shapes) в SVG. Приложението ви трябва да поддържа поне три от тях. Например можете да изберете да се поддържат линия, кръг и правоъгълник. За повече информация за това кои са базовите фигури, вижте https://www.w3.org/TR/SVG/shapes.html.

Също така, за улеснение считаме, че координатната система, в която работим е тази по подразбиране: положителната полуос X сочи надясно, а положителната полуос Y сочи надолу.

Дизайнът на приложението трябва да е такъв, че да позволява при нужда лесно да можете да добавите поддръжка на нови фигури.

Когато зареждате съдържанието на един SVG файл, трябва да прочетете само фигурите, които приложението ви поддържа и можете да игнорирате всички останали SVG елементи.

След като заредите фигурите, потребителят трябва да може да изпълнява дадените в следващия раздел команди, които добавят, изтриват или променят фигурите.

Когато записвате фигурите във файл, трябва да генерирате валиден SVG файл
Операции
След като приложението отвори даден файл, то трябва да може да извършва посочените по-долу операции, в допълнение на общите операции (open, close, save, save as, help и exit):

print
Извежда на екрана всички фигури.
create
Създава нова фигура.
erase &lt;n&gt;
Изтрива фигура с пореден номер &lt;n&gt;.
translate [&lt;n&gt;]
Транслира фигурата с пореден номер &lt;n&gt; или всички фигури, ако &lt;n&gt; не е указано.
within &lt;option&gt; ...
Извежда на екрана всички фигури, които изцяло се съдържат в даден регион. Потребителят може да укаже чрез &lt;option&gt; какъв да бъде регионът – кръг (circle) или правоъгълник (rectangle)

open figures.svg
Successfully opened figures.svg

&gt; print
1. rectangle 5 5 10 10 green
2. circle 5 5 10 blue
3. rectangle 100  60 10 10 red

&gt; create rectangle -1000 -1000 10 20 yellow
Successfully created rectangle (4)

&gt; print
1. rectangle 1 1 10 20 green
2. circle 5 5 10 blue
3. rectangle 100 60 10 10 red
4. rectangle 1000 1000 10 20 yellow

&gt; within rectangle 0 0 30 30
1. rectangle 5 5 10 10 green
2. circle 5 5 10 blue

&gt; within circle 0 0 5
No figures are located within circle 0 0 5

&gt; erase 2
Erased a circle (2)

&gt; erase 100
There is no figure number 100!

&gt; print
1. rectangle 5 5 10 10 green
2. rectangle 100 60 10 10 red
3. rectangle 1000 1000 10 20 yellow

&gt; translate vertical=10 horizontal=100
Translated all figures

&gt; print
1. rectangle 105 15 10 10 green
2. rectangle 200 70 10 10 red
3. rectangle 1100 1010 10 20 yellow

&gt; save
Successfully saved the changes to figures.svg

&gt; exit
Exit