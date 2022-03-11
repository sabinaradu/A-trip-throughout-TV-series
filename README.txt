functia get_bit selecteaza bitii, masca fiind rezultatul shiftarii la stanga al bitului 1 cu  i (numarul bitului).
masca este rezultatul operatiei AND dintre aceasta si nr. daca conditia mastii este indeplinita atunci rezultatul este 1, altfel este 0.
functia flip_bit transforma bitul 1 in 0 si 0 in 1. masca este rezultatul shiftarii la stanga al bitului 1 cu i pozitii.
apoi, rezultatul se obtine facand operatia XOR intre numar si masca.
la functia activate_bit, bit activ inseamna ca e 1 iar activarea unui bit inseamna trecerea lui din 0 in 1. rezultatul este reprezentat in hexazecimal si se obtine prin operatia OR dintre nr si masca.
la functia clear_bit, masca este obtinuta prin shiftarea la stanga 1 cu i pozitii iar apoi se neaga cu ajutorul operatiei de NOT, transformand bitii de 1 in 0 si invers. apoi, res se obtine facand operatia AND intre nr si masca.
functia nand_gate returneaza rezultatul negat al operatiei AND dintre a si b. 
and_gate are ca variabila part, pe care o foloseste in functia nand_gate pt a afla rezultatul.
not_gate foloseste de asemenea functia nand_gate.
idem or_gate si xor_gate.
la task 1, am scos ultimul carry si am facut sumator pe biti cu full adder. daca ies carry in afara da 0, iar suma a fost reconstruita intr-un numar bit cu bit.
in functia recv_message, se initializeaza len ca fiind lungimea codificata, care se shifteaza la stanga cu 2 pozitii si apoi la dreapta cu 4 pozitii si se returneaza fiecare caracter decodificat.
comm_message initializeaza un mesaj de o lungime length. daca mesajul primit are ultimul caracter P se trimite PICKLERICK care are lungimea 10, care se codifica si se trimite, la fel si caracterele cu ajutorul functiei send_squanch.
la send_squanch2 masca se obtine prin shiftarea la stanga a 1 cu i pozitii. shiftarea rezultatului operatiei AND dintre masca si c1 la dreapta cu i pozitii se opereaza cu OR si asa se obtine temp. acesta devine ulterior shiftarea acestuia la stanga cu o pozitie. Idem in cazul lui c2. new char este noul byte format si se obtine prin shiftarea lui temp la stanga cu i*2 pozitii.
functia find_spell gaseste 16 biti care se afla in memorie dupa un grup de 5 biti de 1. masca se obtine prin shiftarea bitului 1 cu i pozitii. if ul returneaza 1 doar daca si masca si memoria sunt 1, atunci counter creste. se opreste cand ajunge la 5 si a gasit grupul. rezultatul este obtinut prin shiftarea memoriei la dreapta cu i+1 pozitii
functia find_key gaseste 16 biti care se afla in memorie inaintea unui grup de 3 biti de 1. astfel, masca se obtine prin shiftarea la stanga a bitului 1 cu i pozitii. Idem ca la functia de dinainte doar ca if ul se opreste cand conter ajunge la 3 biti de 1. rezultatul este shiftarea memoriei la dreapta cu i+1 -counter-16.
decript_spell foloseste XOR pentru a gasi spell.