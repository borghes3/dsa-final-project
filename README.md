# Prova finale 

**Lingua / Language:**  
[🇮🇹 Italiano](#italiano) | [🇬🇧 English](#english)

---

> [!WARNING]
> 🇮🇹: Il codice finale sará aggiunto alla repository solo dopo il termine della finestra di presentazione del progetto.\
> 🇬🇧: The final code will be added to the repository only after the end of the project presentation window.

## (Italiano) 🇮🇹 Prova finale: Progetto di Algoritmi e Strutture Dati

Il progetto é stato completato al termine del corso di "Algoritmi e Principi dell'Informatica" sostenuto presso il Politecnico di Milano durante l'anno accademico 2024/25.

### Valutazione finale
- Valutazione finale: 30 e lode
- Tempo di esecuzione: 9.1 secondi
- Memoria occupata: 21.2 MiB
> [!IMPORTANT]
> Tempo e memoria sono stati valutati da verificatore automatico i cui casi di test sono ignoti agli studenti.

### Specifica del progetto
Movhex è una compagnia di autotrasporti che dispone di una flotta di veicoli dispersi su un’ampia area geografica.  
Al fine di minimizzare i costi, Movhex ti ha commissionato l’implementazione di un programma che aiuti nel calcolo delle rotte ottimali per i suoi mezzi.

Il programma da realizzare modella la superficie del pianeta con una mappa formata da piastrelle esagonali di uguali dimensioni.  
La mappa è piastrellata in modo rettangolare, e quindi composta da un numero fissato di righe e colonne, specificate all’inizio dell’esecuzione del programma.

Ogni piastrella esagonale della mappa è connessa a esattamente sei altre piastrelle, fatte salvo quelle che costituiscono i bordi della mappa.  
Ogni esagono è identificato univocamente dai suoi indici di colonna e riga, in quest’ordine. Gli indici iniziano da zero e numerano da sinistra verso destra, dal basso verso l’alto.  
L’esagono `(0, 1)` è collocato sul lato in alto a destra dell’esagono `(0, 0)`.


Gli autoveicoli percorrono rotte spostandosi da un esagono a un altro ad esso collegato.  
Ogni esagono è collegato a tutti quelli ad esso adiacenti sulla mappa.  
Durante l’esecuzione, gli esagoni possono ottenere o perdere collegamenti tramite **rotte aeree**.  

- Una rotta aerea è identificata univocamente dalla coppia ordinata dei due esagoni che essa collega monodirezionalmente.  
- Ogni rotta aerea è dotata di un costo di attraversata.  
- Da ogni esagono partono al più **5 rotte aeree**.

Ad ogni esagono è associato un numero naturale:  
- Se positivo, rappresenta il **costo di uscita via terra** dall’esagono.  
- Il valore `0` indica che l’esagono non può essere abbandonato (ma può essere visitato).  
- Il costo minimo è `1`, il massimo `100`.  

Spostarsi da un esagono a un altro ad esso collegato ha un costo pari al numero associato all’esagono di partenza.  
Il costo di uscita via terra e il costo di attraversata delle rotte aeree può variare durante l’esecuzione del programma.

#### Comandi
Il programma riceve comandi da **standard input** e risponde su **standard output**.  
Ogni risposta termina con `\n`.

Le parole tra parentesi angolate `⟨...⟩` rappresentano variabili.  
Tutti i valori interi sono a 32 bit.

##### `init ⟨n. colonne⟩ ⟨n. righe⟩`
Inizializza (o reinizializza) la mappa di dimensioni ⟨n. righe⟩ × ⟨n. colonne⟩.  
- Tutti gli esagoni hanno costo iniziale `1`.  
- Nessuna rotta aerea è presente.  
- Risposta: `OK`.

##### `change_cost ⟨x⟩ ⟨y⟩ ⟨v⟩ ⟨raggio⟩`

- ⟨x⟩, ⟨y⟩: coordinate di un esagono.  
- ⟨v⟩: intero tra `-10` e `10`.  
- ⟨raggio⟩: intero positivo.

Il costo viene modificato secondo la formula:
```
costo(xe, ye) = costo(xe, ye) + ⌊ ⟨v⟩ × max(0, (⟨raggio⟩ − DistEsagoni(xe, ye, ⟨x⟩, ⟨y⟩)) / ⟨raggio⟩ ) ⌋
```
dove `DistEsagoni(...)` rappresenta il numero minimo di esagoi da percorrere per arrivare dal primo al secondo.

- Risponde `KO` se ⟨x⟩ e ⟨y⟩ non indicano un esagono valido, o se ⟨raggio⟩ = 0.  
- Altrimenti risponde `OK`.

##### `toggle_air_route ⟨x1⟩ ⟨y1⟩ ⟨x2⟩ ⟨y2⟩`
Aggiunge (se assente) o rimuove (se presente) una rotta aerea tra due esagoni.  

- Il costo della nuova connessione è la **media (per difetto)** tra i costi di tutte le connessioni aeree uscenti dall’esagono `(x1, y1)` e il suo costo di uscita via terra.  
- Risponde `OK` se:
  - le coordinate sono valide,  
  - `(x1, y1)` non ha già 5 rotte aeree uscenti.  
- Altrimenti risponde `KO`.

##### `travel_cost ⟨xp⟩ ⟨yp⟩ ⟨xd⟩ ⟨yd⟩`

Restituisce il **costo minimo** per raggiungere `(xd, yd)` da `(xp, yp)` sommando:  
- costi delle connessioni aeree,  
- costi di uscita via terra degli esagoni attraversati.  
- Il costo di uscita dell’esagono di destinazione è ignorato.  
- Se partenza = destinazione, costo = `0`.  
- Se si usa una connessione aerea, il costo di uscita via terra dell’esagono sorgente è ignorato.  
- Risponde `-1` se le coordinate non sono valide o se non esiste un percorso.
---

## (English) 🇬🇧 Final assignment: Data Structures and Algorithms Project 

The project was completed at the end of the "Algoritmi e Principi dell'Informatica" course I attended at Politecnico di Milano during the 2024/25 academic year.

### Final Evaluation
- Final grade: 30 with honors
- Execution time: 9.1 seconds
- Memory usage: 21.2 MiB
> [!IMPORTANT]
> Time and memory were evaluated by an automatic checker whose test cases are unknown to the students.

### Project requirements
Movhex is a transportation company that manages a fleet of vehicles spread over a wide geographical area.  
In order to minimize costs, Movhex has commissioned you to implement a program that assists in calculating the optimal routes for its vehicles.

The program to be developed models the surface of the planet with a map made of hexagonal tiles of equal size.  
The map is tiled in a rectangular way, and therefore consists of a fixed number of rows and columns, specified at the beginning of the program execution.

Each hexagonal tile on the map is connected to exactly six other tiles, except for those on the edges of the map.  
Each hexagon is uniquely identified by its column and row indices, in that order. The indices start at zero and number from left to right, from bottom to top.  
The hexagon `(0, 1)` is located on the upper right side of hexagon `(0, 0)`.

Vehicles travel routes by moving from one hexagon to another that is connected to it.  
Each hexagon is connected to all those adjacent to it on the map.  
During execution, hexagons may gain or lose connections through **air routes**.  

- An air route is uniquely identified by the ordered pair of the two hexagons it connects unidirectionally.  
- Each air route has a traversal cost.  
- Each hexagon can have at most **5 outgoing air routes**.

Each hexagon is associated with a natural number:  
- If positive, it represents the **ground exit cost** from the hexagon.  
- The value `0` indicates that the hexagon cannot be exited (but it can be visited).  
- The minimum cost is `1`, the maximum is `100`.  

Moving from one hexagon to another that is connected has a cost equal to the number associated with the starting hexagon.  
The ground exit cost and the traversal cost of air routes may change during the execution of the program.

#### Commands
The program receives commands from **standard input** and responds on **standard output**.  
Each response ends with `\n`.

Words inside angle brackets `⟨...⟩` represent variables.  
All integer values are 32-bit.

##### `init ⟨n. columns⟩ ⟨n. rows⟩`
Initializes (or reinitializes) the map of size ⟨n. rows⟩ × ⟨n. columns⟩.  
- All hexagons have an initial cost of `1`.  
- No air routes are present.  
- Response: `OK`.

##### `change_cost ⟨x⟩ ⟨y⟩ ⟨v⟩ ⟨radius⟩`

- ⟨x⟩, ⟨y⟩: coordinates of a hexagon.  
- ⟨v⟩: integer between `-10` and `10`.  
- ⟨radius⟩: positive integer.

The cost is modified according to the formula:
```
cost(xe, ye) = cost(xe, ye) + ⌊ ⟨v⟩ × max(0, (⟨radius⟩ − DistHex(xe, ye, ⟨x⟩, ⟨y⟩)) / ⟨radius⟩ ) ⌋
```

where `DistHex(...)` represents the minimum number of hexagons to traverse to go from the first to the second.

- Responds with `KO` if ⟨x⟩ and ⟨y⟩ do not indicate a valid hexagon, or if ⟨radius⟩ = 0.  
- Otherwise responds with `OK`.

##### `toggle_air_route ⟨x1⟩ ⟨y1⟩ ⟨x2⟩ ⟨y2⟩`
Adds (if absent) or removes (if present) an air route between two hexagons.  

- The cost of the new connection is the **average (rounded down)** of the costs of all existing outgoing air connections from hexagon `(x1, y1)` and its ground exit cost.  
- Responds with `OK` if:
  - the coordinates are valid,  
  - `(x1, y1)` does not already have 5 outgoing air routes.  
- Otherwise responds with `KO`.

##### `travel_cost ⟨xp⟩ ⟨yp⟩ ⟨xd⟩ ⟨yd⟩`

Returns the **minimum cost** to reach `(xd, yd)` from `(xp, yp)` by summing:  
- air route traversal costs,  
- ground exit costs of the hexagons traversed.  
- The exit cost of the destination hexagon is ignored.  
- If source = destination, cost = `0`.  
- If an air route is used, the ground exit cost of the source hexagon of that air route is ignored.  
- Responds with `-1` if the coordinates are invalid or if no path exists.
