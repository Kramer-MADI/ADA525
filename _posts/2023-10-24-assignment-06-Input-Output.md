---
layout: post
title:  "Assignment 06: Input-Output"
date:   2023-09-01 16:05:56 +0200
categories: jekyll update
---

`Lysdiode styring basert på sinusbølger`

På denne assignmenten her har jeg valgt å gjøre noe som nødvendigvis ikke handler særlig om prosjektet. Nemlig sample vekselspenning fra en myDaq, og utifra det bestemme når en lysdiode skal skrus av og på med styring fra en Arduino. 

Første jeg gjorde var å få bestemme hvilken sinusbølge myDaq skulle levere. Dette gjorde jeg via NI sin "Arbitrary Waveform" generator. Bestemte spenningen til 5V peak to peak, og passet på å forskyve bølgen slik at den går fra 0 til 5 og ikke -2,5 til 2,5. Det er fordi Arduino er ikke fan av å bli påført negativ spenning. 

![Bølge gen](https://github.com/Kramer-MADI/ADA525/blob/gh-pages/assets/bolge-gen.png?raw=true)

Videre leverer myDaq spenning fra utgang A0 1, og kobler denne utgangen til A0 på arduinoen for å kunne lese verdiene. 

Videre satt jeg opp koden min for å styre dioden som skal skru av og på annhver periode etter sinus bølgen. For å gjøre dette er det nødvendig å sample verdier fra sinusbølgen som arduinoen vil si varierer fra 0 til 1024 bit. dvs. 0 bit = 0V 512 bit = 2.5V og 1024 bit = 5V. de første if setningene i loopen min sørger for at avlesningen starter på et bestemt sted i perioden, og setter en tid som skal sammelignes videre for å sample spenninger med en gitt frekvens. Denne satt jeg til 20 pr. sekund som, burde være mer enn nok for å se ca. når sinus bølgen krysser null punkt når frekvensen på spenningen er 1 Hz.

Til slutt setter jeg opp noen if setninger som forteller hvor verdiene befinner seg i perioden til spenningen, om spenningen øker, synker og når neste periode starter. Dette sammen med modulo funksjonen vil gjøre at dioden går på i ca. 1 sekund annet hvert sekund. Grunnen til at jeg sier ca. er fordi her blir det en god del avvik som feks. sampling bruker en del tid. Fra arduinonen ar lest verdien til den ber dioden gå på så er ikke spenningen lengre den samme. samtidig skal man ha en del flaks for at arduinoen leser nøyaktig 512bit når jeg har bedt programmet mitt sample 20 verdier i sekundet. For å få blinkingen til å bli mer nøyaktig vil det ta rimelig mye tid å løse, og det fungerer som tenkt slik det er nå.

![resultat](https://github.com/Kramer-MADI/ADA525/blob/gh-pages/assets/diode-resultat.gif?raw=true)

![arduino kode](https://raw.githubusercontent.com/Kramer-MADI/ADA525/gh-pages/assets/diode_styrt_av_sineWave.ino)
