# LOG

## 2020-03-23
Lade upp filerna från min gamla repo till hit, med kod för hemsidan och för bilen
Allt i kod-delen funkar perfekt, behöver bara bygga vidare på bilen

## 2020-03-24
Till mestadels försökt (och misslyckats) med att förbättra bilens svängning, då servot svängs runt sig själv ibland vilket gör att själva bilen inte svänger lika mycket

## 2020-03-27
Lagt upp en stream på sidan, inte min stream, men nu vet jag hur det funkar och att det funkar, bara GoPro delen och förbättrad styrning kvar

## 2020-03-31
Tillfälle 1: Börjat konfigurera GoPro-kameran som ska mountas på bilen. Senare skall jag åka till Sp1sen och bygga robot och cadda hållare till GoPro

Tillfälle 2: GoPron kan sända live, ca. 5 sekunders delay men kan bero på dåligt wifi hemma, men 5 sekunders delay är ändå hanterbart, inga extremt snabba rörelser är nödvändiga om man skulle vilja använda den utanför ens synfält

## 2020-04-20
Har förbättrat bilens svängning med justeringar till hjulens distans från själva bilen. Har även kommenterat all kod samt gjort att allting som görs loggas till en AWS DynamoDB databas
Har även arbetat med miniprojektet, då jag gärna ville ha upp lite grejer på en websida men jag gav upp då jag bestämde mig för att nöja mig med där jag är just nu med miniprojektet

Den första test-streamen då en viss Martin Pind kunde styra driverboten tog plats idag mellan 14:10-14:30. Den gode herren lyckades navigera den runtom ett vardagsrum samt göra många imponerande donuts. Det verkar alltså vara möjligt att styra den även i mindre utrymmen och med hög delay

## 2020-04-21
Den andra test-streamen tog plats under detta tillfälle då både Martin Pind samt Ludvig Bylund lyckades köra denna driverbot, och denna gång gjordes det ännu mer effektivt än den första test-streamen då de lyckades köra driverboten runt vardagsrummet samt till köket, och de lyckades köra under ett bord och sedan ta sig ut från det genom att navigera runt stolben som befann sig i närheten

## 2020-04-28
Den tredje test-streamen tog plats under detta tillfälle, och Martin Pind lyckades styra den till dess nuvarande gränser. Han lyckades köra den genom vardagsrummet till köket, till min systers sovrumm samt ut till ytterdörren. Där blev dock uppkopplingen för svag för att live-streamen skulle kunna fortsätta, och streamen frös. Detta är för att GoPron och mikrokontrollern båda kopplar upp sig mot husets wifi, och behöver då lyda under dess gränser. I framtiden kan en portable router mountas på driverboten, men just nu är den inte tillräckligt stor för det och stora justeringar skulle behöva göras, och eftersom projektet börjar dra sig mot sitt slut så finner jag ej tid för att göra detta. Så för tillfället kan den köras runt i detta hus

## Miniprojekt
Har varit slarvig med att uppdatera det som hänt med miniprojektet här, så dumpar några framgångar och motgångar som hänt här under

### 1: 
Miniprojektet var, från början, en stor fil med alla partier, block, ideologier samt funktioner som gör själva valet samt skriver ut allting. Under mars effektiviserades detta genom att implementera flera for-loopar, som kortade ned filen med ca. 50 rader. Efter detta ändrades arkitekturen till projektet så att partierna, blocken och ideologierna var i en fil, och funktionen för att räkna ut valet och skriva ut allting lades som en egen CommonJS modul. Dessa 2 importerades sedan till en run.js fil, som kör val-funktionen från modulen med parametrarna som partierna, blocken och ideologierna från den filen

### 2:
Under tidiga-mitten av april så började en websida byggas upp där man skulle kunna ändra själv vilka partier, block och ideologier som skulle finnas, då man i princip kunde göra allting eget, men det gavs upp på då det blev lite strul med att importera filerna som CommonJS moduler i html-filen, och eftersom tiden började bli knapp så bestämdes det att kommentera och göra färdigt den nuvarande koden och sedan lägga resten av tiden på driverboten
