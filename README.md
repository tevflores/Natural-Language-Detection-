# Natural Language Detection
Implementation of a machine learning algorithm that detects what language a given text file is written in. This was done by employing a method called **n-gram frequency analysis**.


## Machine Learning

Any machine learning project is implemented  with a 2-step process. The first step is to **train** an algorithm on a provided **sample** of data. The algorithm can be trained using the files from the **training_languages folder**. The second step is to test the **trained algorithm** on some files that contain text different from that in the training files. The algorithm is able to predict, with remarkable accuracy, the language that the test file is written in.

## n-gram Frequency Analysis

An **n-gram** is a sequence of n consecutive characters from a given sample of text. For this project, I took **n = 3**. From here on out, I called a sequence of 3 consecutive characters a **trigram**.

The idea behind **trigram frequency analysis** is that the program will measure the **frequency** of each trigram in a given text file. The program counts how many times each trigram occurs in a given text file and will store these frequencies in a vector. Such vectors will be called **frequency vectors**.

It calculates a frequency vector for each of your training languages. Then computes the frequency vector for the test language. Later on, it calculates the **similarity** between the test frequency vector and each of the training frequency vectors. The training frequency vector that yields the highest similarity will correspond to the best matching language.



#### Trigrams

As stated earlier, a **trigram** is a sequence of three consecutive characters from a given string. For example, given the string "hello",  the trigrams are "hel", "ell", and "llo". When calculating what the trigrams are, I considered upper and lower case letters to be the same and ignored any characters that are **not letters**. For example, given the string "This is I.", the trigrams are "thi", "his", "isi", "sis", and "isi".

#### Trigram Frequency Vectors

In order to compute the similarity between two documents, it is necessary to represent the trigram frequencies as vectors in the mathematical sense. Specifically, these vectors need to have the **same number of elements** (i.e. they need to have the same dimension) and **those elements need to be in the same order** across different vectors. The ordering for trigrams will be standardized.

Since we are only concerned with characters in the english alphabet, base-26 encoding can be used. (any characters that are not letters will be ignored, and are treating upper-case letters as if they were lower-case letters.) The unique charracters under consideration are **a-z**. Therefore, we can use vectors that are only 26^3 long. Thus, the encoding you must use is that a maps to 0, b maps to 1, c maps to 2, ... , z maps to 25. With this encoding, the trigram "aaa" would map to 0 and the trigram "zzz" would map to 17,575 (which is 26^3 - 1). As a more useful example, consider the string "This is I.":

* The trigram "thi" maps to the index 19*26^2 + 7*26 + 8 = 13,034. Its frequency is 1.
* The trigram "his" maps to the index 7*26^2 + 8*26 + 18 = 4,958. Its frequency is 1.
* The trigram "isi" maps to the index 8*26^2 + 18*26 + 8 = 5,884. Its frequency is 2.
* The trigram "sis" maps to the index 18*26^2 + 8*26 + 18 = 12,394. Its frequency is 1.
* All other indeces in the frequency vector would contain 0.

**Important note:** the leftmost letter in the most significant digit in our base-26 system.


#### Similarity

Given two vectors (**mathematical vectors, not C++ vectors**), the similarity between those vectors can be described using **cosine similarity**. This is the cosine of the angle between the two vectors.

A formula for the **cosine similarity** of two vectors A and B, where both A and B have n elements is:

<img src="https://latex.codecogs.com/gif.image?\dpi{110}&space;\bg_white&space;\cos^2&space;\theta&space;=&space;\frac{\Big(\sum\limits_{i=0}^{n-1}{A_i&space;B_i}\Big)^2}{\Big(\sum\limits_{i=0}^{n-1}{A_i^2}\Big)&space;\Big(\sum\limits_{i=0}^{n-1}{B_i^2}\Big)}" title="\bg_white \cos^2 \theta = \frac{\Big(\sum\limits_{i=0}^{n-1}{A_i B_i}\Big)^2}{\Big(\sum\limits_{i=0}^{n-1}{A_i^2}\Big) \Big(\sum\limits_{i=0}^{n-1}{B_i^2}\Big)}" />

Numerator:

<img src="http://www.sciweavers.org/tex2img.php?eq=%5Csum%5Climits_%7Bi%3D0%7D%5E%7Bn-1%7D%7BA_i%20B_i%7D%0A&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\sum\limits_{i=0}^{n-1}{A_i B_i}" width="65" height="53" />

Tis is known as the **dot-product** of two vectors.

Denominator:

<img src="http://www.sciweavers.org/tex2img.php?eq=%5Csum%5Climits_%7Bi%3D0%7D%5E%7Bn-1%7D%7BA_i%5E2%7D%0A%0A%0A&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\sum\limits_{i=0}^{n-1}{A_i^2}" width="51" height="53" />

This is the **square-root** of the **sum** of the **element-wise square** of **each element** in the vector A or **norm** of a vector. The same goes for the second term in the denominator.

The value for cosine similarity will range between 0 and 1 inclusive. The larger this value is between two vectors, the more similar they are.

#### Pitfalls

As it so often happens, there are some pitfalls when calculating the similarity between vectors using built-in C++ integer types. The frequency vectors will have some values that are quite large and when these values are squared, they **overlow** even unsigned long long. So, I used **bigints** to get around this issue. the intermediate parts of the similarity calculation will be stored as bigints and then use bigint methods to calculate cos^2 \ theta.

Another thing to notice is that similarity is going to be of type `double`. Since my **bigint** library cannot handle floating-point types, I got around this problem by using **scaled-division**. The idea behind this is:

* take the numerator and multiply it by some convenient number (e.g. 1,000,000),
* perform bigint division using the **scaled numerator**,
* convert the result into a regular integer,
* and finally perform **floating-point division** by 1,000,000
