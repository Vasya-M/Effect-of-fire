# Effect-of-fire
implementation of a simple fire generation algorithm <br />
 ![no image](/img/fire.jpg)
 
 
<p>Математична модель:
Для створення ефекту полум’я використано  класичний алгоритм створення ефекту вогню.
Перш за все потрібно створити палітру кольорів яка змінюватиметься від 0 до 255, і відповідно рівномірно на цьому проміжку від чорного(0) до червоного, оранжевого, і до білого(255).
Другим кроком буде створення двовимірного масиву заданого  розміру. Цей масив буде відображатись в вікні. Для початку весь масив потрібно «занулити»- надати всім коміркам нульове значення (чорний колір)
Третім кроком є функція  яка випадково надає самому нижньому рядку, від його початку та до кінця значень в діапазоні від 240 до 255,
Керуючи параметром випадковості в рішенні чи надавати кольору пікселю чи зробити чорним, можна керувати інтенсивністю вогню і відповідно його висотою
Основним в цьому алгоритмі є обрахування нового значення для кожного пікселю, він подібний до накладання фільтрів, тобто для того щоб отримати нове значення поточного пікселя (відміченого хрестиком) потрібно взяти арифметичну суму від значення поточного, двох нижніх, нижнього правого і лівого  по діагоналі (відмічені зеленим). 
Також потрібно задати коефіцієнт загасання полум’я, бо «чиста» арифметична сума дає повільне рівномірне спадання, тому я ввів такий коефіцієнт, який базується на отриманому значенні пікселя і  на якій висоті він знаходиться  від початку вогню, тобто чим значення більш наближене до нуля і чим вище піксель то й його значення прямуватиме до нуля швидше. Але потрібно перевіряти щоб  піксель не  отримав від’ємне значення.</p>  

Таким чином полум’я буде  з поступовим   з різним за  швидкістю  затуханням  знизу вверх змінюючи свій колір від білого до чорного.
 ![no image](/img/alg.jpg)
 <br />
 Xnew=(Xold+X1+X2+X3+X4)/4
Додаючи попереднє значення для обчислення нового , надає ефекту розмиття так званий “Blur”, або ж іншими словами згладжування.
 <br />
Псевдокод алгоритму створення полум’я:
1.	Створення палітри* 
2.	Створення матриці екрану 
3.	Обнулити матрицю
4.	While(1)
5. Генерація затравки**  для полум’я(контур вогню***)
6. Обрахування значення кожного пікселя
7. Друк  матриці
*-збільшивши розмір палітри можна отримати більшу реалістичність полум’я, бо зросте кількість кольорів які відображатимуть більш плавні переходи між кольорами(зліва 255, справа 900)
  <br />   
**-задаючи частоту  генерування затравки можна регулювати висоту витягування вогню.
***-змінюючи контур вогню, в даній реалізації пряма, то можна отримувати палаючу геометричну фігуру, текст і т. д.
Також була проведена оптимізація- задавши всі параметри вогню можна помітити що при використанні вікна з великою висотою, то вогонь не перевищує певної межі(лінії згасання),тому прораховувати кожен кадр доцільно тільки від цієї лінії згасання.
Блок-схема алгоритму 
 ![no image](/img/block.jpg)


