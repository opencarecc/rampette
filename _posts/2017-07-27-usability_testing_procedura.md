---
layout: post
title: "test di usabilità del prototipo"
subtitle: "risultati e approfondimenti sul test di usabilità del prototipo per la compilazione informatizzata della procedura"
date: 2017-07-27
image: "/assets/images/usertest_procedura.jpg"
categories: ["procedura"]
by: "Alessandro"
excerpt:
lang: it
ref:
published: true
---

Torniamo con un nuovo aggiornamento sulla procedura: risultati e approfondimenti sul test di usabilità del prototipo.

Ci siamo lasciati la scorsa settimana con un post sulla progettazione e lo sviluppo del prototipo per la procedura di regolamentazione. La procedura burocratica è un passaggio necessario per rendere un esercizio commerciale accessibile in regola con la normativa emessa dal Comune di Milano riguardo al regolamento edilizio.
Al momento la procedura è interamente cartacea, non facile da seguire e da riempire. Abbiamo cercato di digitalizzare la maggior parte dei passaggi in modo che un commerciante abbia bisogno solo di un browser per completare la procedura.
Vi rimandiamo a questo post ([link](https://edgeryders.eu/t/openrampette-the-procedure-the-prototype/6491)) per saperne di più sul prototipo della webapp per la compilazione della procedura e sulla ricerca che ha portato a questa soluzione.

**Cosa si fa dopo aver creato un prototipo? Si fa un test!
**Il 12 luglio abbiamo organizzato un incontro pubblico alla Stecca 3.0 di Milano, dove commercianti e altri cittadini hanno potuto provare e dare un feedback sul prototipo.

Dopo aver introdotto i risultati della ricerca iniziale e la metodologia dietro la progettazione del prototipo, abbiamo creato 3 stazioni di prova, ognuna dotata di un computer portatile e un membro del team per prendere appunti ed eventualmente rispondere a dubbi e domande.
Le persone che hanno eseguito il test sono state 9, metà delle quali erano commercianti (la nostra Minerva), una persona con disabilità motorie (il nostro Dioniso) e altri cittadini che si sono presentati perché interessati al progetto.

![](https://edgeryders.eu/uploads/default/original/2X/e/e6984d51dfa5500c9d7f8978ebc0147d8c22350a.jpg)

Abbiamo deciso di eseguire due tipi diversi di test a seconda del tester:
- **NON MODERATO:** A Minerva è stato detto di provare a portare a termine la procedura come se la stesse facendo per il proprio negozio, e commentare ad alta voce o eventualmente fare domande
- **MODERATO:** A Dioniso e tutte le altre persone non facenti parte di una di queste due categorie sono state fornite alcune informazioni preventivamente (altezza ostacolo, larghezza del marciapiede ...) ed è stato chiesto di compiere delle azioni specifiche come se fossero nei panni di Minerva

![](https://edgeryders.eu/uploads/default/original/2X/2/281b92ecc5429dbc07bfb588ee0e2b6bbad81086.jpg)

Durante i test abbiamo ricevuto feedback molto utili su diversi aspetti: architettura dell'informazione, interfaccia utente, navigazione, comprensione del testo, tono di voce, necessità di assistenza.

Ecco alcune citazioni chiave dei tester:

SODDISFATTI

"Il calcolo della pendenza è molto utile"
"La generazione automatica del progetto quotato risolverà il mio problema"

![](https://edgeryders.eu/uploads/default/original/2X/5/5ad61200e77644dbd0e70b5bedda47f4f5f84951.png)

IDEE

"Sarebbe bello poter vedere il modulo compilato prima di scaricarlo, in modo da poter correggere eventuali errori"

![](https://edgeryders.eu/uploads/default/original/2X/9/968a963770857c7483b08d15b6bb27bb0c3b5574.png)

NON CAPISCO...

“Nella schermata modulo A1 sembra che uno debba prendere le misure della pedana e non del marciapiede”
“Come vado alla prossima schermata?”

![](https://edgeryders.eu/uploads/default/original/2X/0/0f37148e091d8d2f01c5a9b8429d1f05fc9976d4.png)

NON SODDISFATTI

"30 minuti per completare è troppo tempo ..."
"Non comprerò una rampa se non sono al 100% sicuro che mi farà rispettare il regolamento"

![](https://edgeryders.eu/uploads/default/original/2X/5/5e679a6acf9e38da51be1d4e27cb5550c578383d.png)

### Patterns di usabilità

Oltre a ciò che i tester dicevano abbiamo potuto osservare dinamiche interessanti nell’utilizzo dell'applicazione:

**Interfaccia utente**

La maggior parte dei tester ha trovato problemi nella navigazione, non trovavano facilmente la call to action quando questa necessita’ uno scroll verso il fondo della pagina
Il 60% dei tester è riuscito al primo tentativo a comprendere e utilizzare gli elementi interattivi in ​​tutto il flusso

**Linguaggio**

La maggior parte degli utenti non legge in modo approfondito il testo prima di procedere alla call to action
La maggior parte degli utenti non riesce ad identificare una differenza sostanziale tra le varie possibili soluzioni e relativi moduli (in particolare tra le soluzioni B e C)
La maggior parte degli utenti ha difficoltà a capire quale sia la soluzione più adatta al loro caso specifico

**Architettura dell'informazione**

La maggior parte degli utenti non capisce di dover comprare (o cercare) una rampa per poterne inserire i dati, quindi completare correttamente la procedura

**Desideri**

Alcuni utenti dimostrano il desiderio di poter completare con questa interfaccia anche la procedura per altri moduli e non solo per il modulo A1

**Preoccupazioni**

Molti utenti sono preoccupati di una pendenza che seppur in regola imponga l’assistenza da parte del commerciante


Tutti i risultati di cui vi abbiamo dati un assaggio qui sopra sono stati raccolti e analizzati.
Questo insieme di dati ci ha dato un punto di partenza per aggiornare il nostro prototipo, in modo da rendere più comprensibile l'architettura delle informazioni e l'interfaccia utente da un lato, e dall’altro prendere atto dei dettagli che dovrebbero essere valutati e discussi per una possibile futura rielaborazione della procedura nella sua interezza.

Potete anche voi provare il prototipo finale [qui](https://share.proto.io/7VVRQ5/) e partecipare alla discussione su [edgeryders](https://edgeryders.eu/t/openrampette-the-procedure-usability-testing/6547).

[Qui](https://docs.google.com/presentation/d/1fZwIjbCm0hnQNvEWd0NL004Do3b3TM0bbtek3OXpPT8/edit#slide=id.g249cfc078e_0_116) trovi alcune slide che riassumono i risultati del test.
