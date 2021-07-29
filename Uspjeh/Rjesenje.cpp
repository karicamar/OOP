
//Izvršiti definiciju funkcija na način koji odgovara opisu(komentarima) datom neposredno uz pozive ili nazive funkcija.Možete dati komentar na bilo koju liniju code - a koju smatrate da bi trebalo unaprijediti ili da će eventualno uzrokovati grešku prilikom kompajliranja.Također, možete dodati dodatne funkcije koje će vam olakšati implementaciju programa.

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <thread>
#include <mutex>
#include <iomanip>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";


const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };

char* GetNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_trenutno = 0;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = obj._trenutno;
		_omoguciDupliranje = obj._omoguciDupliranje;
		_elementi1 = new T1[obj._trenutno];
		_elementi2 = new T2[obj._trenutno];
		for (size_t i = 0; i < obj._trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			delete[]_elementi1; _elementi1 = nullptr;
			delete[]_elementi2; _elementi2 = nullptr;
			_trenutno = obj._trenutno;
			_omoguciDupliranje = obj._omoguciDupliranje;
			_elementi1 = new T1[obj._trenutno];
			_elementi2 = new T2[obj._trenutno];
			for (size_t i = 0; i < obj._trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}
		return *this;
	}
	void AddElement(T1 el1, T2 el2) {
		if (_omoguciDupliranje == false) {
			for (size_t i = 0; i < _trenutno; i++)
			{
				if (el1 == _elementi1[i] && el2 == _elementi2[i])
					throw exception("Dupliranje elemenata");
			}
		}
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;
	}
	Kolekcija<T1, T2>operator()(int start, int end) {
		if (start < 0 || end < 0)
			throw exception("Lokacija manja od 0 ne postoji");
		if (start >= _trenutno || end >= _trenutno)
			throw exception("Lokacija izlazi van opsega kolekcije");
		Kolekcija<T1, T2>novakolekcija;
		for (size_t i = start; i <= end; i++)
		{
			novakolekcija.AddElement(_elementi1[i], _elementi2[i]);
		}
		return novakolekcija;
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj) {
		if (this != &obj) {
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
		}
		return *this;
	}
	bool operator==(const Datum& drugi) {
		return *_dan == *drugi._dan && *_mjesec == *drugi._mjesec && *_godina == *drugi._godina;
	}
	int sumaDana()const {
		return *_dan + *_mjesec * 30 + *_godina * 365;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
};

class Predmet {
	char* _naziv;
	Kolekcija<Datum*, int>* _ocjene;
public:
	Predmet(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
		_naziv = GetNizKaraktera(naziv);
		_ocjene = new Kolekcija<Datum*, int>;
		if (ocjena > 0)
			AddOcjena(datum, ocjena);
	}
	bool AddOcjena(Datum datum, int ocjena) {
		for (size_t i = 0; i < _ocjene->getTrenutno(); i++)
		{
			int razlika = datum.sumaDana() - _ocjene->getElement1(i)->sumaDana();
			if (razlika < 3)
				return false;
		}
		GetOcjene().AddElement(new Datum(datum), ocjena);
		return true;
	}
	Predmet(const Predmet& obj) {
		_naziv = GetNizKaraktera(obj._naziv);
		_ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
	}
	Predmet& operator=(const Predmet& obj) {
		if (this != &obj) {
			delete[] _naziv; _naziv = nullptr;
			delete _ocjene; _ocjene = nullptr;
			_naziv = GetNizKaraktera(obj._naziv);
			_ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
		}
		return *this;
	}
	bool operator==(const Predmet& drugi) {
		return strcmp(_naziv, drugi._naziv) == 0;
	}
	float GetProsjek()const {
		int brojOcjena = _ocjene->getTrenutno();
		if (brojOcjena == 0)
			return 0;
		float suma = 0;
		for (size_t i = 0; i < brojOcjena; i++)
		{
			suma += _ocjene->getElement2(i);
		}
		suma /= brojOcjena;
		return suma;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
		delete _ocjene; _ocjene = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Predmet& obj) {
		COUT << obj._naziv << endl;
		for (int i = 0; i < obj._ocjene->getTrenutno(); i++)
		{
			COUT << *obj._ocjene->getElement1(i) << " " << obj._ocjene->getElement2(i) << endl;
		}
		COUT << "Prosjek: " << obj.GetProsjek() << endl;
		return COUT;
	}
	char* GetNaziv() { return _naziv; }
	Kolekcija<Datum*, int>& GetOcjene() const { return *_ocjene; }
};
class Uspjeh {
	eRazred _razred;
	//char* se odnosi na napomenu o polozenom predmetu
	Kolekcija<Predmet*, const char*> _polozeniPredmeti;
public:
	Uspjeh(eRazred razred = PRVI) {
		_razred = razred;
	}
	Uspjeh(const Uspjeh& obj) {
		_razred = obj._razred;
		_polozeniPredmeti = obj._polozeniPredmeti;
	}
	Uspjeh& operator=(const Uspjeh& obj) {
		if (this != &obj) {
			_razred = obj._razred;
			_polozeniPredmeti = obj._polozeniPredmeti;
		}
		return *this;
	}
	float GetProsjekUspjeh()const {
		int broj = _polozeniPredmeti.getTrenutno();
		if (broj == 0)
			return 0;
		float suma = 0;
		for (size_t i = 0; i < broj; i++)
		{
			suma += _polozeniPredmeti.getElement1(i)->GetProsjek();
		}
		suma /= broj;
		return suma;
	}
	Kolekcija<Predmet*, const char*>& GetPredmeti() { return _polozeniPredmeti; }
	eRazred GetERazred() { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << obj._razred << endl;
		for (size_t i = 0; i < obj._polozeniPredmeti.getTrenutno(); i++)
		{
			COUT << *obj._polozeniPredmeti.getElement1(i) << " " << obj._polozeniPredmeti.getElement2(i) << endl;
		}
		return COUT;
	}
};
/*
   broj telefona mora biti u formatu
   - znak +
   - pozivni broj drzave (2 ili 3 cifre)
   - pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
   - prvi dio broja (2 ili 3 cifre)
   - razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
	- drugi dio broja (2 ili 3 cifre)

   ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
   */
   //if (ValidirajBrojTelefona("+38761222333"))
   //cout << "Broj telefona validan" << crt;
   //if (ValidirajBrojTelefona("+38761222-333"))
   //cout << "Broj telefona validan" << crt;
   //if (ValidirajBrojTelefona("+38761222 333"))
   //cout << "Broj telefona validan" << crt;
   //if (ValidirajBrojTelefona("+387061222 333"))
   //cout << "Broj telefona validan" << crt;
   //if (!ValidirajBrojTelefona("+38761 222 333"))
   //cout << "Broj NIJE telefona validan" << crt;
   //if (!ValidirajBrojTelefona("+387 61222 333"))
   //cout << "Broj NIJE telefona validan" << crt
bool ValidirajBrojTelefona(string telefon) {
	regex reg("\\+[0-9]{2,3}[0]?[0-9]{2}[0-9]{2,3}[ -]?[0-9]{2,3}");
	return regex_match(telefon, reg);

}
mutex m;
mutex m2;
class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = GetNizKaraktera(imePrezime);
		_emailAdresa = emailAdresa;
		if (ValidirajBrojTelefona(brojTelefona))
			_brojTelefona = brojTelefona;
		else
			_brojTelefona = "NOT VALID";

		//izvrsiti validaciju broja telefona
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	///*
   //uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
   //tom prilikom onemoguciti:
   //- dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
   //- dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
   //- dodavanje vise od 5 predmeta na nivou jednog razreda
   //razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
   //Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
   //*/
	bool AddPredmet(eRazred razred, Predmet predmet, const char* napomena) {
		if (predmet.GetProsjek() < 2.5)
			return false;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (_uspjeh[i].GetERazred() == razred) {
				if (_uspjeh[i].GetPredmeti().getTrenutno() >= 5)
					return false;
				for (size_t j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++)
				{
					if (*_uspjeh[i].GetPredmeti().getElement1(j) == predmet)
						return false;
				}
				_uspjeh[i].GetPredmeti().AddElement(new Predmet(predmet), napomena);
				thread t1(&Kandidat::PosaljiPoruku, this, razred, _uspjeh[i].GetProsjekUspjeh(), GetUkupniProsjek());
				t1.join();
				if (_uspjeh[i].GetProsjekUspjeh() > 4.5) {
					thread t2(&Kandidat::PosaljiSMS, this, razred, _uspjeh[i].GetProsjekUspjeh());
					t2.join();
				}
				return true;
			}
		}
		Uspjeh uspjeh(razred);
		uspjeh.GetPredmeti().AddElement(new Predmet(predmet), napomena);
		_uspjeh.push_back(uspjeh);
		thread t1(&Kandidat::PosaljiPoruku, this, razred, uspjeh.GetProsjekUspjeh(), GetUkupniProsjek());
		t1.join();
		if (uspjeh.GetProsjekUspjeh() > 4.5) {
			thread t2(&Kandidat::PosaljiSMS, this, razred, uspjeh.GetProsjekUspjeh());
			t2.join();
		}
		return true;
	}
	Kolekcija<Predmet, float> operator()(Datum* Od, Datum* Do) {
		Kolekcija<Predmet, float>temp;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++)
			{
				bool datumIspravan = false;
				float sumarazlikadana = 0;
				int brojOcjena = _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno();
				for (size_t k = 0; k < brojOcjena; k++)
				{
					int suma = _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k)->sumaDana();
					if (suma >= Od->sumaDana() && suma <= Do->sumaDana())
						datumIspravan = true;
					if (k > 0)
						sumarazlikadana += suma - _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k - 1)->sumaDana();
				}
				if (brojOcjena > 1)
					sumarazlikadana /= brojOcjena - 1;
				if (datumIspravan)
					temp.AddElement(*_uspjeh[i].GetPredmeti().getElement1(j), sumarazlikadana);

			}
		}
		return temp;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		for (size_t i = 0; i < obj._uspjeh.size(); i++)
			COUT << obj._uspjeh[i] << endl;
		return COUT;
	}
	float GetUkupniProsjek()const {
		int broj = _uspjeh.size();
		float suma = 0;
		if (broj == 0)
			return 0;
		for (size_t i = 0; i < broj; i++)
		{
			suma += _uspjeh[i].GetProsjekUspjeh();
		}
		return suma / broj;
	}
	///*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
   //FROM:info@fit.ba
   //TO: emailKorisnika
   //Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
   //na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
   //Pozdrav.
   //FIT Team.

   //ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“


   //slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
   //*/
	void PosaljiPoruku(eRazred razred, float dosadasnjiUspjeh, float UkupniUspjeh) {
		m.lock();
		cout << "FROM:info@fit.ba" << endl;
		cout << "TO: " << GetEmail() << endl;
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << razred << " razred. Dosadasnji uspjeh (prosjek) na nivou " << razred << " razreda iznosi " << dosadasnjiUspjeh << ", a ukupni uspjeh u toku skolovanja iznosi " << UkupniUspjeh << "." << endl;
		cout << "Pozdrav." << endl;
		cout << "FIT Team." << endl;
		m.unlock();
	}
	void PosaljiSMS(eRazred razred, float dosadasnjiUspjeh) {
		m2.lock();
		cout << "Svaka cast za uspjeh " << dosadasnjiUspjeh << " u " << razred << " razredu" << endl;
		m2.unlock();
	}
	vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite ulogu i nacin koristenja generickog tipa future<>?\n";
	return "Odgovor -> ";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
	return "Odgovor -> Virtualno nasljedjivanje omogucava da obnjekti najizvedenijih klasa mogu posjedovati samo jedan podobjekat indirektne blaze klase.";
}

void main() {

	cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	Datum
		datum19062021(19, 6, 2021),
		datum20062021(20, 6, 2021),
		datum30062021(30, 6, 2021),
		datum05072021(5, 7, 2021);

	int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (int i = 0; i <= kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
		kolekcija1.AddElement(3, 3);
	}
	catch (exception & err) {
		cout << err.what() << crt;
	}
	cout << kolekcija1 << crt;

	/*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
	ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
	Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
	cout << kolekcija2 << crt;
	try {
		//primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
		Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
		Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
	}
	catch (exception & err) {
		cout << err.what() << crt;
	}

	//parametri: nazivPredmeta, datum, prva ocjena
	Predmet Matematika("Matematika", datum19062021, 5),
		Fizika("Fizika", datum20062021, 5),
		Hemija("Hemija", datum30062021, 2),
		Engleski("Engleski", datum05072021, 5);

	Matematika.AddOcjena(datum05072021, 3);
	Matematika.AddOcjena(datum05072021, 3);

	// ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
	// ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
	cout << Matematika << endl;


	/*
	broj telefona mora biti u formatu
	- znak +
	- pozivni broj drzave (2 ili 3 cifre)
	- pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
	- prvi dio broja (2 ili 3 cifre)
	- razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
	 - drugi dio broja (2 ili 3 cifre)

	ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
	*/

	if (ValidirajBrojTelefona("+38761222333"))
		cout << "Broj telefona validan" << crt;
	if (ValidirajBrojTelefona("+38761222-333"))
		cout << "Broj telefona validan" << crt;
	if (ValidirajBrojTelefona("+38761222 333"))
		cout << "Broj telefona validan" << crt;
	if (ValidirajBrojTelefona("+387061222 333"))
		cout << "Broj telefona validan" << crt;
	if (!ValidirajBrojTelefona("+38761 222 333"))
		cout << "Broj NIJE telefona validan" << crt;
	if (!ValidirajBrojTelefona("+387 61222 333"))
		cout << "Broj NIJE telefona validan" << crt;


	Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "+38761222333");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "+387061222 333");
	Kandidat brojTelefonaNotValid("Ime Prezime", "korisnik@klix.ba", "+387 61222 333");

	///*
	//uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	//tom prilikom onemoguciti:
	//- dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
	//- dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
	//- dodavanje vise od 5 predmeta na nivou jednog razreda
	//razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	//Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	//*/
	if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
		cout << "Predmet 1 uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
		cout << "Predmet 2 uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
		cout << "Predmet 3 uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
		cout << "Predmet 4 uspjesno dodan!" << crt;
	//Matematiku je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
		cout << "Predmet 5 uspjesno dodan!" << crt;

	///*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	//FROM:info@fit.ba
	//TO: emailKorisnika
	//Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
	//na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
	//Pozdrav.
	//FIT Team.

	//ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“


	//slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	//*/
	cout << jasmin << crt;

	//  vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
	//  float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
	Kolekcija<Predmet, float> jasminUspjeh = jasmin(new Datum(18, 06, 2021), new  Datum(21, 06, 2021));
	cout << jasminUspjeh << crt;

	cin.get();
	system("pause>0");
}
