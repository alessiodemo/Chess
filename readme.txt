Nel caso si voglia effettuare una partita Computer vs Computer, quando si mandera' in esecuzione il programma si dovra' attendere un lasso di tempo corrispondente al tempo necessario al programma per rilevare lo scacco matto di un giocatore , oppure la patta della partita.
Il tempo di attesa potra' risultare nell' ordine di qualche minuto inquanto per garantire la massima randomicita' della funzione rand() che ha il compito di estrarre un indice a caso che identifica il pezzo da muovere avente almeno una mossa disponibile; abbiamo inserito una pausa di 200 ms tra una mossa e l'altra
a causa della dipendenza della funzione rand() dall' ora corrente. Infatti senza questa pausa, il programma nella maggior parte dei casi muove piu' o meno sempre gli stessi pezzi.

Nel caso si esegua una partita Computer vs Computer oppure Computer vs Giocatore Umano, il programma produrra' il file di log della partita con il nome "LogPC.txt".

Il file di log di una partita Computer vs Computer e' denominato con PCvsPC.txt.
Il file di log di una partita Computer vs Giocatore Umano e' denominato con PCvsCC.txt.
