# Compilation audit after corrections

48 standalone programs compiled and linked with GCC 13.3.0 on Linux using C11, `-Wall -Wextra -Wpedantic`. Some legacy warnings remain and are reproduced below. CMake is supplied but was not available in the preparation environment; the Python build was verified. Compilation does not prove all program paths correct.

## `alberi/esercizi.c`

Builds — target `alberi_esercizi`

No compiler diagnostics.

## `alberi/ricercaAlbero.c`

Builds — target `alberi_ricercaAlbero`

No compiler diagnostics.

## `chat1/esercizio2-testo.c`

Builds — target `chat1_esercizio2_testo`

No compiler diagnostics.

## `chat1/fdp_2026_07_13_M2new_turno1_test.c`

Builds — target `chat1_fdp_2026_07_13_M2new_turno1_test`

No compiler diagnostics.

## `chat1/simulazione_adt_vettori_liste_pile_code.c`

Builds — target `chat1_simulazione_adt_vettori_liste_pile_code`

No compiler diagnostics.

## `chat1/simulazione_centri_assistenza.c`

Builds — target `chat1_simulazione_centri_assistenza`

No compiler diagnostics.

## `chat1/testo.c`

Builds — target `chat1_testo`

No compiler diagnostics.

## `compiti anni precedenti/compito 5/testo.c`

Builds — target `compiti_anni_precedenti_compito_5_testo`

```text
exercises/compiti anni precedenti/compito 5/testo.c: In function ‘calcola_e_costruisci_indice’:
exercises/compiti anni precedenti/compito 5/testo.c:426:13: warning: unused variable ‘prob_pioggia’ [-Wunused-variable]
  426 |         int prob_pioggia = impianto->prob_pioggia;
      |             ^~~~~~~~~~~~
exercises/compiti anni precedenti/compito 5/testo.c: In function ‘main’:
exercises/compiti anni precedenti/compito 5/testo.c:485:11: warning: unused variable ‘nuovo_fattore’ [-Wunused-variable]
  485 |     float nuovo_fattore;
      |           ^~~~~~~~~~~~~
exercises/compiti anni precedenti/compito 5/testo.c:484:9: warning: unused variable ‘nuovo_stato_int’ [-Wunused-variable]
  484 |     int nuovo_stato_int;
      |         ^~~~~~~~~~~~~~~
exercises/compiti anni precedenti/compito 5/testo.c:483:10: warning: unused variable ‘buffer_codice’ [-Wunused-variable]
  483 |     char buffer_codice[MAX_CODICE];
      |          ^~~~~~~~~~~~~
```

## `compiti anni precedenti/compito 8/main.c`

Builds — target `compiti_anni_precedenti_compito_8_main`

No compiler diagnostics.

## `compiti anni precedenti/compito 9/main.c`

Builds — target `compiti_anni_precedenti_compito_9_main`

No compiler diagnostics.

## `compiti anni precedenti/compito2/main.c`

Builds — target `compiti_anni_precedenti_compito2_main`

No compiler diagnostics.

## `compiti anni precedenti/compito3/main.c`

Builds — target `compiti_anni_precedenti_compito3_main`

No compiler diagnostics.

## `compiti anni precedenti/compito4/main.c`

Builds — target `compiti_anni_precedenti_compito4_main`

No compiler diagnostics.

## `compiti anni precedenti/compito6/modulo2_testo.c`

Builds — target `compiti_anni_precedenti_compito6_modulo2_testo`

No compiler diagnostics.

## `compiti anni precedenti/compito7/Modulo2_Testo.c`

Builds — target `compiti_anni_precedenti_compito7_Modulo2_Testo`

No compiler diagnostics.

## `compiti anni precedenti/sim1/simulazione_m2_lineari_TODO.c`

Builds — target `compiti_anni_precedenti_sim1_simulazione_m2_lineari_TODO`

No compiler diagnostics.

## `compiti anni precedenti/sim_rec1/testo1.c`

Builds — target `compiti_anni_precedenti_sim_rec1_testo1`

No compiler diagnostics.

## `compiti anni precedenti/sim_rec22/main.c`

Builds — target `compiti_anni_precedenti_sim_rec22_main`

No compiler diagnostics.

## `es1/main.c`

Builds — target `es1_main`

```text
exercises/es1/main.c: In function ‘totale_per_rider’:
exercises/es1/main.c:326:9: warning: unused variable ‘somma’ [-Wunused-variable]
  326 |     int somma = 0;
      |         ^~~~~
exercises/es1/main.c: In function ‘main’:
exercises/es1/main.c:519:13: warning: unused variable ‘vettore_guadagni’ [-Wunused-variable]
  519 |     float * vettore_guadagni = NULL;
      |             ^~~~~~~~~~~~~~~~
exercises/es1/main.c:516:9: warning: unused variable ‘numero_rider’ [-Wunused-variable]
  516 |     int numero_rider = 0;
      |         ^~~~~~~~~~~~
```

## `es2/main.c`

Builds — target `es2_main`

```text
exercises/es2/main.c: In function ‘main’:
exercises/es2/main.c:352:17: warning: unused variable ‘aux_prest’ [-Wunused-variable]
  352 |     TListaLibri aux_prest;
      |                 ^~~~~~~~~
exercises/es2/main.c:351:17: warning: unused variable ‘aux_disp’ [-Wunused-variable]
  351 |     TListaLibri aux_disp;
      |                 ^~~~~~~~
```

## `es3/simulazione_m2_ticket.c`

Builds — target `es3_simulazione_m2_ticket`

No compiler diagnostics.

## `eser12magg/taxi.c`

Builds — target `eser12magg_taxi`

```text
exercises/eser12magg/taxi.c: In function ‘main’:
exercises/eser12magg/taxi.c:419:12: warning: unused variable ‘elem_taxi’ [-Wunused-variable]
  419 |     T_Taxi elem_taxi;
      |            ^~~~~~~~~
```

## `eser17apr/task01.c`

Builds — target `eser17apr_task01`

No compiler diagnostics.

## `eser17apr/task02.c`

Builds — target `eser17apr_task02`

No compiler diagnostics.

## `eser17apr/task03.c`

Builds — target `eser17apr_task03`

```text
exercises/eser17apr/task03.c: In function ‘main’:
exercises/eser17apr/task03.c:330:15: warning: unused variable ‘elem’ [-Wunused-variable]
  330 |         Libro elem;
      |               ^~~~
```

## `eser19magg/log_sito_web.c`

Builds — target `eser19magg_log_sito_web`

```text
exercises/eser19magg/log_sito_web.c: In function ‘stampaAccessiPerUtente’:
exercises/eser19magg/log_sito_web.c:105:13: warning: unused variable ‘i’ [-Wunused-variable]
  105 |         int i;
      |             ^
```

## `eser20magg/coda_ordini.c`

Builds — target `eser20magg_coda_ordini`

No compiler diagnostics.

## `eser3giugno/agenda_telefonica.c`

Builds — target `eser3giugno_agenda_telefonica`

No compiler diagnostics.

## `eser5giugno/testo.c`

Builds — target `eser5giugno_testo`

```text
exercises/eser5giugno/testo.c: In function ‘main’:
exercises/eser5giugno/testo.c:441:17: warning: unused variable ‘aux_prest’ [-Wunused-variable]
  441 |     TListaLibri aux_prest;
      |                 ^~~~~~~~~
exercises/eser5giugno/testo.c:440:17: warning: unused variable ‘aux_disp’ [-Wunused-variable]
  440 |     TListaLibri aux_disp;
      |                 ^~~~~~~~
```

## `eser5magg/supermercato.c`

Builds — target `eser5magg_supermercato`

```text
exercises/eser5magg/supermercato.c: In function ‘main’:
exercises/eser5magg/supermercato.c:312:20: warning: unused variable ‘articolo’ [-Wunused-variable]
  312 |         T_Prodotto articolo;
      |                    ^~~~~~~~
```

## `eser6magg/task01/task1.c`

Builds — target `eser6magg_task01_task1`

No compiler diagnostics.

## `eser6magg/task02/task2.c`

Builds — target `eser6magg_task02_task2`

No compiler diagnostics.

## `eser6magg/task03/task3.c`

Builds — target `eser6magg_task03_task3`

No compiler diagnostics.

## `eser8magg/task01/task01.c`

Builds — target `eser8magg_task01_task01`

No compiler diagnostics.

## `eser8magg/task02-03/task02.c`

Builds — target `eser8magg_task02_03_task02`

No compiler diagnostics.

## `eser8magg/task02-03/task03.c`

Builds — target `eser8magg_task02_03_task03`

No compiler diagnostics.

## `eser9giugno/testo.c`

Builds — target `eser9giugno_testo`

```text
exercises/eser9giugno/testo.c: In function ‘main’:
exercises/eser9giugno/testo.c:564:13: warning: unused variable ‘vettore_guadagni’ [-Wunused-variable]
  564 |     float * vettore_guadagni = NULL;
      |             ^~~~~~~~~~~~~~~~
exercises/eser9giugno/testo.c:561:9: warning: unused variable ‘numero_rider’ [-Wunused-variable]
  561 |     int numero_rider = 0;
      |         ^~~~~~~~~~~~
```

## `hw1/task1.c`

Builds — target `hw1_task1`

No compiler diagnostics.

## `hw1/task2.c`

Builds — target `hw1_task2`

No compiler diagnostics.

## `hw1/task3.c`

Builds — target `hw1_task3`

No compiler diagnostics.

## `hw1/task4.c`

Builds — target `hw1_task4`

No compiler diagnostics.

## `newSim1/main.c`

Builds — target `newSim1_main`

```text
exercises/newSim1/main.c: In function ‘elabora_prossima_richiesta’:
exercises/newSim1/main.c:396:20: warning: unused variable ‘temp’ [-Wunused-variable]
  396 |     NodoRichiesta *temp;
      |                    ^~~~
exercises/newSim1/main.c: In function ‘ripristina_ultima_richiesta’:
exercises/newSim1/main.c:502:20: warning: unused variable ‘temp’ [-Wunused-variable]
  502 |     NodoElaborata *temp;
      |                    ^~~~
```

## `project1/moltiplicazione_matrici.c`

Builds — target `project1_moltiplicazione_matrici`

No compiler diagnostics.

## `sim1706.2/main.c`

Builds — target `sim1706_2_main`

No compiler diagnostics.

## `sim24aug/simulazione_finale_adt_tutte_varianti.c`

Builds — target `sim24aug_simulazione_finale_adt_tutte_varianti`

No compiler diagnostics.

## `sim24aug/simulazione_m2_basi_droni.c`

Builds — target `sim24aug_simulazione_m2_basi_droni`

No compiler diagnostics.

## `sim3/main.c`

Builds — target `sim3_main`

No compiler diagnostics.

## `sim4/main.c`

Builds — target `sim4_main`

No compiler diagnostics.

