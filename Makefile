all: bayes_digit bayes_face perceptron_digit perceptron_face knn_digit knn_face

bayes_digit: bayes_digit.c
	gcc -o bayes_digit bayes_digit.c bayes_digit_util.c -lm

bayes_face: bayes_face.c
	gcc -o bayes_face bayes_face.c bayes_face_util.c -lm

perceptron_digit: perceptron_digits.c
	gcc -o perceptron_digit perceptron_digits.c perceptron_digits_util.c 

perceptron_face: perceptron_face.c
	gcc -o perceptron_face perceptron_face.c perceptron_face_util.c

knn_digit: knn_digits.c
	gcc -o knn_digit knn_digits.c knn_digits_util.c -lm

knn_face: knn_face.c
	gcc -o knn_face knn_face.c knn_face_util.c -lm


