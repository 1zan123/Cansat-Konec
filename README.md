🚀 CanSat Projekt
Opis naloge:

CanSat je simulacija pravega satelita, vgrajenega v prostornino in obliko pločevinke za brezalkoholne pijače.
Izziv za sodelujoče je, da v to minimalno prostornino umestijo vse glavne podsisteme satelita, kot so:

🔋 napajanje
🌡️ senzorji
📡 komunikacijski sistem
CanSat se nato izstreli z raketo do višine približno enega kilometra, ali pa se spusti s platforme, brezpilotnega letala ali balona.

Po izstrelitvi se začne njegova misija, ki vključuje:

izvedbo znanstvenega poskusa
primarno in sekundarno nalogo
predstavitev uporabljene tehnologije
varen pristanek
in analizo zbranih podatkov.
🎯 Cilj projekta je uspešna izvedba celotne misije in čim bolj natančna zbirka podatkov ob čim manjših dimenzijah sistema.

🧰 Kosovnica (seznam uporabljenih komponent)
Št.	Komponenta	Opis ali funkcija
1	Arduino Uno	Glavni mikrokrmilnik za upravljanje sistema
2	Bakrene žičke	Povezave med komponentami
3	Proto Shield	Razširitvena plošča za spajkanje
4	Li-Ion baterija 18650 (4800 mAh)	Napajanje sistema
5	DHT22	Senzor temperature in vlage
6	NEO-6M GPS modul	Sprejem GPS koordinat
7	HMC5883L	Magnetni kompas / merjenje smeri
8	BMP280	Senzor tlaka in višine
9	MPU6050	Pospeškometer in žiroskop
10	APC220 x2	Brezžični RF komunikacijski moduli
11	Yagi antena	Usmerjena antena za sprejem podatkov
12	3D printano ohišje	Zaščita komponent (iz filamenta)
13	Padalo iz poliestrske svile	Varen pristanek sistema
14	Poliestrske vrvice	Povezava padala z ohišjem
15	Prenosni računalnik	Spremljanje, zbiranje in analiza podatkov
16	Miška	Upravljanje računalnika
17	Majhna tipka	Uporabniški vmesnik za prižig baterije ter vseh komponent
Priredbeni seznam – Projekt: CanSat
VHODI:
Senzor / Modul	VCC	GND	DATA / RX / SDA	DRUGI PIN (npr. SCL / TX / RESET)	Opombe
SENZOR_TEMP (DHT22)	5V	GND	D2		Potrebuje 10kΩ pull-up upor
GPS modul (NEO-6M)	5V	GND	RX → D4	TX → D3	Serijska komunikacija (SoftSerial)
KOMPAS (HMC5883L)	3V	GND	SDA → A4	SCL → A5	I2C komunikacija
VIŠINOMER (BMP280)	3V	GND	SDA → A4	SCL → A5	I2C komunikacija
POSPEŠKOMER (MPU6050)	3V	GND	SDA → A4	SCL → A5	I2C komunikacija
RADIO_RX (APC220)	5V	GND	RX → D8	TX → D9	Serijska komunikacija (SoftSerial)
TIPKA_RESET		GND	D6		Digitalni vhod
IZHODI:
Izhod / Modul	PIN na Arduino	VCC (če potrebuje)	GND (če potrebuje)	Signalni pin	Opombe
LED_TEMP	D2				LED indikator za temperaturo
LED_GPS	D3				LED indikator za GPS signal
LED_OK	D4				LED indikator za pravilno delovanje
LED_ERROR	D8				LED indikator za napako
RADIO_TX (APC220)	D9	5V	GND	TX → D9	Serijska komunikacija (SoftSerial)
📌 Priredbeni seznam (Pinout)
Št.	Komponenta	Signal / Pin na komponenti	Arduino Pin	Opombe
1	DHT22	DATA	D2	Digitalni pin (temperatura/vlaga)
2	NEO-6M GPS	TX	D4 (RX Arduino)	Serijska komunikacija (SoftSerial)
RX	D3 (TX Arduino)	--
3	HMC5883L	SDA / SCL	A4 / A5	I2C komunikacija
4	BMP280	SDA / SCL	A4 / A5	I2C (skupna vodila z drugimi)
5	MPU6050	SDA / SCL	A4 / A5	I2C (skupna vodila z drugimi)
6	APC220 (TX modul)	TX	D9 (RX Arduino)	Serijska komunikacija (SoftSerial)
RX	D8 (TX Arduino)	--
7	Majhna tipka	OUT	D6	Pull-down uporaba
8	Yagi antena	--	Povezana z APC220	Pasivna – ni direktno na Arduino
9	Li-Ion baterija	+ / -	VIN / GND	Napajanje Arduina
10	Proto Shield	--	Na Arduino	Fizična razširitev vezja
