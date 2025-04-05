# progconc_prodInt
Repository for an activity for the Concurrent Programming Uni subject. This project implements the inner product of two vectors of N size and N random float vallues each.

**How to use it**
I made two bash scripts in order to compile and run the c programs smoothly.
First you run the gerarVetores.sh. If you run without passing arguments, it will generate 3 binary files called teste_N5, teste_N10 and teste_N15 wich corresponds to two vector of sizes N=5, N=10 and N=15. If you run passing a number as argument, it will create a testeN{number} binary file for you.

After generating the vectors and saving them to the binary files, execute the gerarProdInt.sh passing two arguments, the first one is the name of the file and the second one is the number of threads you want the program to use.

**WARNING**: For the number of threads, choose a number that divides the vector size in equal parts. The threads will not work properly otherwise.

If you want to see the vector values, uncomment the #define TEXTO bit.
