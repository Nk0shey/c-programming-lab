# Compilation audit

48 standalone C11 programs compiled with GCC 13.3.0, `-Wall -Wextra -Wpedantic`. CMake and CTest were executed successfully. See AUDIT.md for runtime coverage and remaining work. This JSON/Markdown audit is report data; the build reads CMakeLists.txt.

## `alberi/esercizi.c`

Target: `alberi_esercizi`. Build passed.

No compiler diagnostics.

## `alberi/ricercaAlbero.c`

Target: `alberi_ricercaAlbero`. Build passed.

No compiler diagnostics.

## `chat1/esercizio2-testo.c`

Target: `chat1_esercizio2_testo`. Build passed.

No compiler diagnostics.

## `chat1/fdp_2026_07_13_M2new_turno1_test.c`

Target: `chat1_fdp_2026_07_13_M2new_turno1_test`. Build passed.

No compiler diagnostics.

## `chat1/simulazione_adt_vettori_liste_pile_code.c`

Target: `chat1_simulazione_adt_vettori_liste_pile_code`. Build passed.

No compiler diagnostics.

## `chat1/simulazione_centri_assistenza.c`

Target: `chat1_simulazione_centri_assistenza`. Build passed.

No compiler diagnostics.

## `chat1/testo.c`

Target: `chat1_testo`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito 5/testo.c`

Target: `compiti_anni_precedenti_compito_5_testo`. Build passed.

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

Target: `compiti_anni_precedenti_compito_8_main`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito 9/main.c`

Target: `compiti_anni_precedenti_compito_9_main`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito2/main.c`

Target: `compiti_anni_precedenti_compito2_main`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito3/main.c`

Target: `compiti_anni_precedenti_compito3_main`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito4/main.c`

Target: `compiti_anni_precedenti_compito4_main`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito6/modulo2_testo.c`

Target: `compiti_anni_precedenti_compito6_modulo2_testo`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/compito7/Modulo2_Testo.c`

Target: `compiti_anni_precedenti_compito7_Modulo2_Testo`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/sim1/simulazione_m2_lineari_TODO.c`

Target: `compiti_anni_precedenti_sim1_simulazione_m2_lineari_TODO`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/sim_rec1/testo1.c`

Target: `compiti_anni_precedenti_sim_rec1_testo1`. Build passed.

No compiler diagnostics.

## `compiti anni precedenti/sim_rec22/main.c`

Target: `compiti_anni_precedenti_sim_rec22_main`. Build passed.

No compiler diagnostics.

## `es1/main.c`

Target: `es1_main`. Build passed.

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

Target: `es2_main`. Build passed.

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

Target: `es3_simulazione_m2_ticket`. Build passed.

No compiler diagnostics.

## `eser12magg/taxi.c`

Target: `eser12magg_taxi`. Build passed.

```text
exercises/eser12magg/taxi.c: In function ‘main’:
exercises/eser12magg/taxi.c:419:12: warning: unused variable ‘elem_taxi’ [-Wunused-variable]
  419 |     T_Taxi elem_taxi;
      |            ^~~~~~~~~
```

## `eser17apr/task01.c`

Target: `eser17apr_task01`. Build passed.

No compiler diagnostics.

## `eser17apr/task02.c`

Target: `eser17apr_task02`. Build passed.

No compiler diagnostics.

## `eser17apr/task03.c`

Target: `eser17apr_task03`. Build passed.

```text
exercises/eser17apr/task03.c: In function ‘main’:
exercises/eser17apr/task03.c:330:15: warning: unused variable ‘elem’ [-Wunused-variable]
  330 |         Libro elem;
      |               ^~~~
```

## `eser19magg/log_sito_web.c`

Target: `eser19magg_log_sito_web`. Build passed.

```text
exercises/eser19magg/log_sito_web.c: In function ‘stampaAccessiPerUtente’:
exercises/eser19magg/log_sito_web.c:105:13: warning: unused variable ‘i’ [-Wunused-variable]
  105 |         int i;
      |             ^
```

## `eser20magg/coda_ordini.c`

Target: `eser20magg_coda_ordini`. Build passed.

No compiler diagnostics.

## `eser3giugno/agenda_telefonica.c`

Target: `eser3giugno_agenda_telefonica`. Build passed.

No compiler diagnostics.

## `eser5giugno/testo.c`

Target: `eser5giugno_testo`. Build passed.

```text
exercises/eser5giugno/testo.c: In function ‘main’:
exercises/eser5giugno/testo.c:386:17: warning: unused variable ‘aux_prest’ [-Wunused-variable]
  386 |     TListaLibri aux_prest;
      |                 ^~~~~~~~~
exercises/eser5giugno/testo.c:385:17: warning: unused variable ‘aux_disp’ [-Wunused-variable]
  385 |     TListaLibri aux_disp;
      |                 ^~~~~~~~
```

## `eser5magg/supermercato.c`

Target: `eser5magg_supermercato`. Build passed.

```text
exercises/eser5magg/supermercato.c: In function ‘main’:
exercises/eser5magg/supermercato.c:312:20: warning: unused variable ‘articolo’ [-Wunused-variable]
  312 |         T_Prodotto articolo;
      |                    ^~~~~~~~
```

## `eser6magg/task01/task1.c`

Target: `eser6magg_task01_task1`. Build passed.

No compiler diagnostics.

## `eser6magg/task02/task2.c`

Target: `eser6magg_task02_task2`. Build passed.

No compiler diagnostics.

## `eser6magg/task03/task3.c`

Target: `eser6magg_task03_task3`. Build passed.

No compiler diagnostics.

## `eser8magg/task01/task01.c`

Target: `eser8magg_task01_task01`. Build passed.

No compiler diagnostics.

## `eser8magg/task02-03/task02.c`

Target: `eser8magg_task02_03_task02`. Build passed.

No compiler diagnostics.

## `eser8magg/task02-03/task03.c`

Target: `eser8magg_task02_03_task03`. Build passed.

No compiler diagnostics.

## `eser9giugno/testo.c`

Target: `eser9giugno_testo`. Build passed.

```text
exercises/eser9giugno/testo.c: In function ‘main’:
exercises/eser9giugno/testo.c:543:13: warning: unused variable ‘vettore_guadagni’ [-Wunused-variable]
  543 |     float * vettore_guadagni = NULL;
      |             ^~~~~~~~~~~~~~~~
exercises/eser9giugno/testo.c:540:9: warning: unused variable ‘numero_rider’ [-Wunused-variable]
  540 |     int numero_rider = 0;
      |         ^~~~~~~~~~~~
```

## `hw1/task1.c`

Target: `hw1_task1`. Build passed.

No compiler diagnostics.

## `hw1/task2.c`

Target: `hw1_task2`. Build passed.

No compiler diagnostics.

## `hw1/task3.c`

Target: `hw1_task3`. Build passed.

No compiler diagnostics.

## `hw1/task4.c`

Target: `hw1_task4`. Build passed.

No compiler diagnostics.

## `newSim1/main.c`

Target: `newSim1_main`. Build passed.

```text
exercises/newSim1/main.c: In function ‘elabora_prossima_richiesta’:
exercises/newSim1/main.c:362:20: warning: unused variable ‘temp’ [-Wunused-variable]
  362 |     NodoRichiesta *temp;
      |                    ^~~~
exercises/newSim1/main.c: In function ‘ripristina_ultima_richiesta’:
exercises/newSim1/main.c:468:20: warning: unused variable ‘temp’ [-Wunused-variable]
  468 |     NodoElaborata *temp;
      |                    ^~~~
```

## `project1/moltiplicazione_matrici.c`

Target: `project1_moltiplicazione_matrici`. Build passed.

No compiler diagnostics.

## `sim1706.2/main.c`

Target: `sim1706_2_main`. Build passed.

No compiler diagnostics.

## `sim24aug/simulazione_finale_adt_tutte_varianti.c`

Target: `sim24aug_simulazione_finale_adt_tutte_varianti`. Build passed.

No compiler diagnostics.

## `sim24aug/simulazione_m2_basi_droni.c`

Target: `sim24aug_simulazione_m2_basi_droni`. Build passed.

No compiler diagnostics.

## `sim3/main.c`

Target: `sim3_main`. Build passed.

No compiler diagnostics.

## `sim4/main.c`

Target: `sim4_main`. Build passed.

No compiler diagnostics.

