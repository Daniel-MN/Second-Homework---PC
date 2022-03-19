//Mușuroi Daniel-Nicușor
//Grupa: 313CB
//PC - Tema 2


				A Game of Scrabble

	
	Pentru fiecare task am creat o functie pe care am apelat-o in main in
functie de cerinta data.
	Am declarat global matricea game_board si vectorul pentru scorurile
literelor numit scor_litere.
	Pentru realizarea taskurilor am creat cateva functii ajutatoare pe care
le-am folosit in cadrul taskurilor:
	-citeste_N -> citeste un numar aflat singur pe o linie
	-citeste_string -> citeste un string aflat pe o linie (stringul
"Y X D cuvant")
	-code_line -> codeaza coordonatele (Y, X, D) si cuvantul intr-un string
	-scrie_cuvant -> scrie un cuvant la coordonatele date in matricea 
game_board
	-set_score -> seteaza scorul fiecarei litere in vectorul scor_litere.
	-scor_cuv -> calculeaza scorul unui cuvant inainte de adaugarea
bonusurilor
	-scor_final_cuv -> calculeaza scorul final al cuvantului, tinand cont
de bonusuri si implicit de pozitia cuvintelor pe tabla
	-scor_final_player -> calculeaza scorul unui player tinand cont de
cuvintele jucate, de coordonatele acestora (liniile jucate)
	-verf_jucat -> verifica daca un cuvant a fost jucat
	-verf_cuvant -> verifica daca un cuvant poate fi scris pe orizontala
sau pe verticala astfel incat sa nu se suprapuna cu alte cuvinte. Daca se poate
scrie pe orizontala returneaza 0, iar daca nu se poate scrie pe orizontala, dar
se poate scrie pe verticala returneaza 1. Daca nu se poate scrie nici pe 
orizontala, nici pe verticala returneaza -1.


		TASK 0: task_0

	Nu sunt prea multe lucruri de spus, doar pune '.' in fiecare loc din
matricea game_board.
	
		TASK 1: task_1

	Apeleaza task_0 pentru a pune '.' in matrice, apoi citeste N si fiecare
linie (folosind functiile de citire citeste_N si citeste_string), urmand sa scrie
cuvintele apeland functia scrie_cuvant.

		TASK 2: task_2

	Calculeaza scorul fiecarui player netinand cont de bonusuri (folosind 
functia scor_cuv), apoi afiseaza cele doua scoruri in formatul dorit.

		TASK 3: task_3

	Calculeaza scorul fiecarui player folosind functia scor_final_player
care primeste ca parametri numarul playerului, liniile jucate, numarul de linii
jucate si stringurile de bonus. Afiseaza apoi cele doua scoruri in formatul
dorit.

		TASK 4: task_4

	Functia task_4 citeste toate cuvintele, le scrie pe tabla, salveaza
cuvintele intr-o matrice si in final apeleaza functia alege_cuvant_task_4. 
Functia alege_cuvant_task_4 ia cuvintele in ordine din lista de cuvinte 
si verifica daca cuvantul a mai fost scris cu ajutorul functiei verf_jucat,
apoi verifica tabla incepand din colt stanga sus, linie cu linie, pana la colt
dreapta jos pentru a afla daca se poate scrie acel cuvant. Se gaseste primul
cuvant care se poate scrie si se face acest lucru folosind functia scrie_cuvant.

		TASK 5: task_5

	Functia task_5 face in mare ceea ce face si functia task_4, doar ca 
foloseste o functie alege_cuvant_task_5. Functia alege_cuvant_task_5 ia fiecare
cuvant din lista, verifica daca acesta a fost jucat, apoi verifica daca se poate
scrie pe tabla si daca da, verifica daca scorul acelui cuvant e mai mare decat
diferenta de scor dintre cei doi playeri. Astfel, se vor retine coordonatele si
cuvantul cu cel mai mare scor posibil ( mai mare decat diferenta de scor dintre
cei doi playeri ). La final va scrie cuvantul gasit pe tabla si va afisa tabla.
Daca nu gaseste niciun cuvant va afisa mesajul "Fail!".

		TASK 6: task_6
		
	Functia task_6 citeste stringurile de bonus, citeste numarul de linii
(numarul de cuvinte pe care player 1 le va scrie pe tabla). Dupa fiecare linie
citita, scrie cuvantul pe tabla, apoi cu ajutorul functiei alege_cuvant_task_6
se obtine cuvantul optim jucat de player 2, care se scrie pe tabla. La final 
se afiseaza tabla si cu ajutorul functiei who_won se afiseaza cine a castigat.
	Functia alege_cuvant_task_6 ia fiecare cuvant din lista , verifica daca
a fost jucat, apoi verifica daca se poate scrie pe tabla. Se vor retine
coordonatele si cuvantul cu cel mai mare scor posibil, care vor fi codate
intr-o linie precum cele primite ca input, linie ce va fi returnata 
(nu se ia in seama diferenta de scor dintre cei doi playeri, important fiind
doar ca player 2 sa aleaga cuvantul cu punctajul cel mai mare).
	Functia who_won calculeaza la final dupa cele 2 * N ( N numarul de 
cuvinte jucate de player 1 ) cuvinte jucate punctajele fiecarui player si
stabileste castigatorul afisand un mesaj corespunzator.



		In main doar se citeste cerinta si corespunzator fiecarei
cerinte se apeleaza una dintre functiile task_i (i=0,1,2,3,4,5,6). Pentru
task_0 am folosit print_board(game_board) in main deoarece am mai folosit
functia task_0 in alte taskuri.