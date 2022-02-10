# Dont-touch-the-spikes-Programowanie-I-Projekt
Projekt realizowany na koniec semestru z przedmiotu Programowanie

# Opis projektu.
Projekt jest próbą odwzorowania popularnej gry mobilnej „don't touch the spikes”. Jest to gra zręcznościowa o bardzo prostym wykonaniu lecz wymagającym poziomem trudności. Sterowanie ogranicza się do jednej operacji, klikaniu spacji gdy chcemy aby nasz ptak wzniósł się w górę. Akcja odgrywa się w zamkniętym pomieszczeniu. Na jego ścianach co pewien czas w losowych miejscach wyłaniają się kolce. Nasze zadanie polega na unikaniu ich i przetrwaniu jak najdłużej.

# Funkcjonalności 
-	wykonanie w całości w środowisku graficznym przy wsparciu biblioteki SFML 2.5.1,
-	wzbogacenie o efekty dźwiękowe,
-	będzie zawierał w pełni funkcjonalne menu pozwalające na: 
-	rozpoczęcie gry,
-	sprawdzenie naszych najlepszych poprzednich wyników,
-	nauki sterowania,
-	wyjście z gry,
-	zliczanie punktów na żywo w naszym podejściu
-	przechowywanie wyników z 10 naszych najlepszych podejść

# Przebieg realizacji
## Pliki niezbędne do poprawnego działania programu:
-	main.cpp – rozpoczyna grę wykorzystując konstruktor klasy Game, 
-	definitions.h – zawiera różne stałe wykorzystywane podczas pracy programu (np. szerokość wyświetlanego ekranu),
-	Game.h/Game.cpp – przechowuję niezbędne dane do prawidłowego wyświetlania gry oraz poprawnego zarządzania stanami gry,
-	State.h – jest to klasa z której dziedziczy każdy „State” dzięki czemu jest możliwa płynne przechodzenie pomiędzy nimi,
-	StateMachine.h/ StateMachine.cpp – odpowiada za zarządzanie „State’ami”. Posiada stos na którym trzymane są wszystkie aktywne „State’y”. Umożliwia ich zmianie, dodawanie i usuwanie. Zwraca do klasy Game najwyższy „State” na stosie,
-	SplashState.h/SplashState.cpp – zawiera kod prezentowanego ekranu powitalnego po włączeniu gry,
-	MenuState.h/MenuState.cpp – jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń menu,
-	GameState.h/GameState.cpp - jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń podczas rozgrywki,
-	ScoreboardState.h/ScoreboardState.cpp - jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń po przejściu do „Tabela wynikow”,
-	ScoreMachine.h/ScoreMachine.cpp – odpowiada za zarządzanie zapisanymi wynikami, ich zapisywanie, odczytywanie, sortowanie, odrzucanie tych najgorszych oraz zwracanie najlepszego,
-	scoreboard.bin – zawiera zapis naszych 10 najlepszych wyników wraz z datami,
-	RulesState.h/RulesState.cpp - jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń po przejściu do „Jak grac?”,
-	GameState.h/GameState.cpp - jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń podczas rozgrywki,
-	GameOverState.h/GameOverState.cpp - jest to element odpowiedzialny za wyświetlanie i obsługę zdarzeń podsumowującego aktualną próbę,
-	src (folder) – zawiera grafiki oraz dźwięki wykorzystywane podczas działania programu,

Do korzystania z programu wymagana jest także zewnętrzna biblioteka SFML (Simple and Fast Multimedia Library). Jest to wieloplatformowa biblioteka ułatwiająca tworzenie gier oraz programów multimedialnych. Jest napisana w C++ i może być wykorzystywana w takich językach jak: C, platformie .NET, D, Pythonie, Javie.
SFML obsługuje akcelerację sprzętową grafiki 2D przy użyciu OpenGL. Biblioteka jest otwartym oprogramowaniem wydanym na licencji zlib.
W skład SFML wchodzi pięć modułów:
-	System – obsługuje czas i wątki,
-	Window – obsługuje okna i interakcję z użytkownikiem,
-	Graphics – umożliwia renderowanie grafiki,
-	Audio – dostarcza interfejsu do odtwarzania muzyki i dźwięków,
- Network – odpowiedzialny za komunikację sieciową,
