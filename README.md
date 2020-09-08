# RKmethod

Program jest częścią pracy licencjackiej powstałej w 2018 roku.

Kod programu został napisany w języku C++ przy pomocy ogólnodostępnej biblioteki SFML.
Do napisania programu użyte zostało środowisko CodeBlocks. 
Użyte biblioteki są w wersji SFML 2.4.2 z kompilatorem GCC 6.1.0 MinGW (DW2).

Celem programu jest zobrazowanie zadanych układów równań różniczkowych, których rozwiązanie
metodami analitycznymi jest niemożliwe.

Program został skonstruowany w taki sposób, że nie mozna w nim podawać
własnych warunków początkowych dla zadanych układów. Jest to celowy zabieg. Nie spowodowałoby
to żadnych problemów obliczeniowych, a jedynie wizualne (które w pracy były bardzo ważne). 
Wprowadzanie warunków początkowych wymagałoby bardzo dużej kontroli nad tym,
co wpisuje uzytkownik - wartości, które mógłby podać jako warunki początkowe,
musiałyby być bliskie podanym w pracy, ponieważ układy te mają charakter chaotyczny.
Oznacza to, że układy te przy pewnych warunkach początkowych zachowują się nieprzewidywalnie
(zobrazowanie rozwiązania mogłoby okazać się niemożliwe). Przez to ich trajektorie
można zobrazować tylko przy odpowiednio dobranych warunkach oraz
skalowaniu.

Przy uruchamianiu aplikacji należy brać pod uwagę, że okno programu
ma rozdzielczość 1280x800. Ze wzgledu na to, że program jest napisany z
naciskiem na dokładność obliczeń i graficznych odwzorowań, rysowanie wykresów
i poruszanie się między ekranem rzutów a menu głównym wymaga
oczekiwania maksymalnie pięciu do siedmiu sekund.

Ze względu na ograniczenia wprowadzania warunków początkowych w
opisanej aplikacji dołączony jest też konsolowy program, dzięki któremu
można sprawdzić rachunki pojawiające się w metodzie Rungego-Kutty
dla dowolnych wartości (wyniki zostają wyeksportowane do pliku).

Martyna Wiśniewska

