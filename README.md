# 🚀 CanSat Projekt
**Opis naloge:**

CanSat je simulacija pravega satelita, vgrajenega v prostornino in obliko pločevinke za brezalkoholne pijače.  
Izziv za sodelujoče je, da v to minimalno prostornino umestijo vse glavne podsisteme satelita, kot so:

- 🔋 napajanje  
- 🌡️ senzorji  
- 📡 komunikacijski sistem  

CanSat se nato izstreli z raketo do višine približno **enega kilometra**, ali pa se spusti s platforme, brezpilotnega letala ali balona.

Po izstrelitvi se začne njegova misija, ki vključuje:
- izvedbo **znanstvenega poskusa**
- **primarno in sekundarno nalogo**
- predstavitev uporabljene **tehnologije**
- **pristanek**
- in **analizo zbranih podatkov**.



🎯 Cilj projekta je uspešna izvedba celotne misije in čim bolj natančna zbirka podatkov ob čim manjših dimenzijah sistema.
## 🧰 Kosovnica (seznam uporabljenih komponent)

| Št. | Komponenta                                     | Opis ali funkcija                                |
|-----|------------------------------------------------|--------------------------------------------------|
| 1   | Arduino Uno                                    | Glavni mikrokrmilnik za upravljanje sistema      |
| 2   | Bakrene žičke                                  | Povezave med komponentami                        |
| 3   | Proto Shield                                   | Razširitvena plošča za spajkanje                 |
| 4   | Li-Ion baterija 18650 (4800 mAh)               | Napajanje sistema                                |
| 5   | DHT22                                          | Senzor temperature in vlage                      |
| 6   | NEO-6M GPS modul                               | Sprejem GPS koordinat                            |
| 7   | HMC5883L                                       | Magnetni kompas / merjenje smeri                 |
| 8   | BMP280                                         | Senzor tlaka in višine                           |
| 9   | MPU6050                                        | Pospeškometer in žiroskop                        |
| 10  | APC220 x2                                      | Brezžični RF komunikacijski moduli               |
| 11  | Yagi antena                                    | Usmerjena antena za sprejem podatkov             |
| 12  | 3D printano ohišje                             | Zaščita komponent (iz filamenta)                 |
| 13  | Padalo iz poliestrske svile                    | Varen pristanek sistema                          |
| 14  | Poliestrske vrvice                             | Povezava padala z ohišjem                        |
| 15  | Prenosni računalnik                            | Spremljanje, zbiranje in analiza podatkov        |
| 16  | Miška                                           | Upravljanje računalnika                          |
| 17  | Majhna tipka                                   | Uporabniški vmesnik za prižig baterije ter vseh komponent       |




## Priredbeni seznam – Projekt: CanSat

### VHODI:

| **Senzor / Modul**        | **VCC** | **GND** | **DATA / RX / SDA** | **DRUGI PIN (npr. SCL / TX / RESET)** | **Opombe**                         |
| ------------------------- | ------- | ------- | ------------------- | ------------------------------------- | ---------------------------------- |
| **SENZOR\_TEMP (DHT22)**  | 5V      | GND     | D2                  |                                       | Potrebuje 10kΩ pull-up upor        |
| **GPS modul (NEO-6M)**    | 5V      | GND     | RX → D4             | TX → D3                               | Serijska komunikacija (SoftSerial) |
| **KOMPAS (HMC5883L)**     | 3V      | GND     | SDA → A4            | SCL → A5                              | I2C komunikacija                   |
| **VIŠINOMER (BMP280)**    | 3V      | GND     | SDA → A4            | SCL → A5                              | I2C komunikacija                   |
| **POSPEŠKOMER (MPU6050)** | 3V      | GND     | SDA → A4            | SCL → A5                              | I2C komunikacija                   |
| **RADIO\_RX (APC220)**    | 5V      | GND     | RX → D8             | TX → D9                               | Serijska komunikacija (SoftSerial) |
| **TIPKA\_RESET**          |         | GND     | D6                  |                                       | Digitalni vhod                     |

---



### IZHODI:

| **Izhod / Modul**      | **PIN na Arduino** | **VCC (če potrebuje)** | **GND (če potrebuje)** | **Signalni pin** | **Opombe**                          |
| ---------------------- | ------------------ | ---------------------- | ---------------------- | ---------------- | ----------------------------------- |
| **LED\_TEMP**          | D2                 |                        |                        |                  | LED indikator za temperaturo        |
| **LED\_GPS**           | D3                 |                        |                        |                  | LED indikator za GPS signal         |
| **LED\_OK**            | D4                 |                        |                        |                  | LED indikator za pravilno delovanje |
| **LED\_ERROR**         | D8                 |                        |                        |                  | LED indikator za napako             |
| **RADIO\_TX (APC220)** | D9                 | 5V                     | GND                    | TX → D9          | Serijska komunikacija (SoftSerial)  |

---



## 📌 Priredbeni seznam (Pinout)

| Št. | Komponenta            | Signal / Pin na komponenti | Arduino Pin       | Opombe                             |
| --- | --------------------- | -------------------------- | ----------------- | ---------------------------------- |
| 1   | **DHT22**             | DATA                       | D2                | Digitalni pin (temperatura/vlaga)  |
| 2   | **NEO-6M GPS**        | TX                         | D4 (RX Arduino)   | Serijska komunikacija (SoftSerial) |
|     |                       | RX                         | D3 (TX Arduino)   | --                                 |
| 3   | **HMC5883L**          | SDA / SCL                  | A4 / A5           | I2C komunikacija                   |
| 4   | **BMP280**            | SDA / SCL                  | A4 / A5           | I2C (skupna vodila z drugimi)      |
| 5   | **MPU6050**           | SDA / SCL                  | A4 / A5           | I2C (skupna vodila z drugimi)      |
| 6   | **APC220 (TX modul)** | TX                         | D9 (RX Arduino)  | Serijska komunikacija (SoftSerial) |
|     |                       | RX                         | D8 (TX Arduino)  | --                                 |
| 7   | **Majhna tipka**      | OUT                        | D6                | Pull-down uporaba                  |
| 8   | **Yagi antena**       | --                         | Povezana z APC220 | Pasivna – ni direktno na Arduino   |
| 9   | **Li-Ion baterija**   | + / -                      | VIN / GND         | Napajanje Arduina                  |
| 10  | **Proto Shield**      | --                         | Na Arduino         | Fizična razširitev vezja           |




SLIKA VEZALNE SHEME:

![image](https://github.com/user-attachments/assets/857757d5-d407-4fcd-92af-c7359655dc45)



SLIKA VEZAVE:

![slika](https://github.com/user-attachments/assets/4c402d88-32a0-49e9-801a-44c165c83c3a)

VIDEO DELOVANJA SENZORJEV:

https://github.com/user-attachments/assets/a6660e66-6f19-4cc9-bf77-eccf6020bfdd




PRIMER IZPISA:

![sdsdas](https://github.com/user-attachments/assets/d1e169d5-b2d7-4431-bcc5-13005865432f)

#Zgornja slika prikazuje izpis, ki ni popolnoma viden v videu, sam izpis ne vsebuje gpsa saj so seznorji delovali takrat znotraj šole, znotraj šole kjer gps ne deluje.


![image](https://github.com/user-attachments/assets/6405df92-1e27-42c1-9bec-c91c5989427d)

#Gps nam je izpisoval točno lokacijo naše šole, ko je bil ta uporabljen odzunaj, zgorja slika je primer točnega izpisa lokacije.






✅ Kaj je šlo po načrtu
Senzorji so delovali brez težav.

Program za zajem in prenos podatkov je bil stabilen in zanesljiv.

Kapsula je bila mehansko ustrezno zasnovana in izdelana.

Testiranja padala so pokazala primerne hitrosti spuščanja, skladne s pričakovanji.

⚠️ Kaj ni šlo po načrtu
Širina kapsule je presegala dovoljene mere glede na pravila tekmovanja.

Povezava z anteno ni delovala, zato prenos podatkov med letom ni bil mogoč.

Nekateri senzorji so bili napačno dostavljeni ali so prispeli prepozno.

Komunikacija v ekipi ni bila vedno optimalna, kar je povzročilo nekaj nesporazumov.

🔁 Kaj bi naredili drugače naslednjič
Projekt bi začeli pravočasneje, s čimer bi si zagotovili več časa za razvoj in testiranje.

Uporabili bi bolj natančne in zanesljive senzorje.

Poseben poudarek bi namenili izboljšanju komunikacije znotraj ekipe.

Predhodno bi testirali vse komunikacijske module, še posebej brezžične prenose.

🤝 Sodelovanje v ekipi
Delo je bilo večinoma enakomerno porazdeljeno med člane.

Nekateri člani so imeli nekoliko več zadolžitev, a so jih uspešno opravili.

Kljub izzivom smo dobro sodelovali in dosegli skupne cilje.



