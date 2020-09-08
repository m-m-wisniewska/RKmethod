# RKmethod

Program jest częścią pracy licencjackiej powstałej w 2018 roku.

Kod programu został napisany w języku C++ przy pomocy ogólnodostępnej biblioteki SFML.
Do napisania programu użyte zostało środowisko CodeBlocks. 
Użyte biblioteki są w wersji SFML 2.4.2 z kompilatorem GCC 6.1.0 MinGW (DW2).

Celem programu jest zobrazowanie zadanych układów równań różniczkowych, których rozwiązanie
metodami analitycznymi jest niemożliwe.

Program został skonstruowany w taki sposób, ze nie mozna w nim podawac
własnych warunków poczatkowych dla zadanych układów. Jest to celowy zabieg. Nie spowodowałoby
to zadnych problemów obliczeniowych, a jedynie wizualne (które w pracy były bardzo ważne). 
Wprowadzanie warunków poczatkowych wymagałoby bardzo duzej kontroli nad tym,
co wpisuje uzytkownik - wartosci, które mógłby podać jako warunki początkowe,
musiałyby byc bliskie podanym w pracy, poniewaz układy te maja charakter chaotyczny.
Oznacza to, że układy te przy pewnych warunkach początkowych zachowują się nieprzewidywalnie
(zobrazowanie rozwiązania mogłoby okazać się niemożliwe). Przez to ich trajektorie
mozna zobrazowac tylko przy odpowiednio dobranych warunkach oraz
skalowaniu.

Przy uruchamianiu aplikacji nalezy brac pod uwage, ze okno programu
ma rozdzielczosc 1280x800. Ze wzgledu na to, ze program jest napisany z
naciskiem na dokładnosc obliczen i graficznych odwzorowan, rysowanie wykresów
i poruszanie sie miedzy ekranem rzutów a menu głównym wymaga
oczekiwania maksymalnie pieciu do siedmiu sekund.

Ze wzgledu na ograniczenia wprowadzania warunków poczatkowych w
opisanej aplikacji dołaczony jest tez konsolowy program, dzieki któremu
mozna sprawdzic rachunki pojawiajace sie w metodzie Rungego-Kutty
dla dowolnych wartosci (wyniki zostają wyeksportowane do pliku).

Martyna Wiśniewska

