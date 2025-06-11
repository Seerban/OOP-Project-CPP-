import java.util.Scanner;

public class Service {
    Portofel port;
    PartInventar pinv;
    MasinaInventar minv;
    Client[] clienti;

    ClientDB clientdb;
    PartDB partdb;
    MasinaDB masinadb;
    PortofelDB portofeldb;
    Scanner scanner;
    
    public Service(Scanner in) {
        port = new Portofel(0);
        pinv = new PartInventar(20);
        minv = new MasinaInventar(20);
        clienti = new Client[20];
        this.scanner = in;
        clientdb = new ClientDB(in);
        partdb = new PartDB(in);
        masinadb = new MasinaDB(in);
        portofeldb = new PortofelDB(in);
    }
    
    public void showBal() {
        //port.view();
        portofeldb.getAll();
    }

    public void tranzactie() {
        System.out.println("Valoare: ");
        int val = scanner.nextInt();
        portofeldb.tranzactie(val);
    }

    public void veziPart() {
        //db.selectAll("Part");
        partdb.getAll();
    }

    public void veziMasini() {
        //minv.show();
        masinadb.getAll();
    }

    public void veziClienti() {
        /*for(int i=0; i<clienti.length; ++i)
            if( clienti[i] != null )
                System.out.println(clienti[i]); */
        //db.selectAll("Client");
        clientdb.getAll();
    }

    public void adaugaMasina() {
        /*System.out.println("Adauga Masina:");
        int index;

        Part[] parti = pinv.getParti();

        System.out.println("Nume masina: ");
        String nume = scanner.next();

        System.out.println("Sasiu alegeri: ");
        for(int i=0; i< pinv.getCapacitate(); i++ ) if ( parti[i] != null) if ( parti[i].getCategorie() == Part.Categorie.Sasiu ) System.out.println( Integer.toString(i) + " " +parti[i] );
        index = scanner.nextInt();
        Part sasiu = pinv.pop( index );
        
        System.out.println("Roti alegeri: ");
        for(int i=0; i< pinv.getCapacitate(); i++ ) if ( parti[i] != null) if ( parti[i].getCategorie() == Part.Categorie.Roti ) System.out.println( Integer.toString(i) + " " +parti[i] );
        index = scanner.nextInt();
        Part roti = pinv.pop(index);
        
        System.out.println("Motor alegeri: ");
        for(int i=0; i< pinv.getCapacitate(); i++ ) if ( parti[i] != null) if ( parti[i].getCategorie() == Part.Categorie.Motor ) System.out.println( Integer.toString(i) + " " + parti[i] );
        index = scanner.nextInt();
        Part motor = pinv.pop(index);

        System.out.println("Pret (recomandat " + ((sasiu.getPret() + roti.getPret() + motor.getPret()) * 2) + "):");
        int pret = scanner.nextInt();
        Masina masina = new Masina(nume, sasiu, roti, motor, pret);
        minv.adauga(masina);*/
        masinadb.insert();
    }   

    public void adaugaPart() {
        /*System.out.println("Adauga part: ( nume, pret, an, categorie(Motor/Roti/Sasiu) )");
        String nume, cat_aux;
        int pret, an;
        nume = scanner.next();
        pret = scanner.nextInt();
        an = scanner.nextInt();
        cat_aux = scanner.next();
        Part.Categorie cat;
        switch(cat_aux) {
            case "Motor" -> cat = Part.Categorie.Motor;
            case "Roti" -> cat = Part.Categorie.Roti;
            case "Sasiu" -> cat = Part.Categorie.Sasiu;
            default -> cat = null;
        }
        Part p = new Part(nume, pret, an, cat);
        pinv.adauga(p);*/
        partdb.insert();
    }

    public void adaugaClient() {
        /*System.out.println("Nume: ");
        String nume = scanner.next();
        Client aux = new Client(nume);
        for(int i=0; i < clienti.length; ++i) 
            if( clienti[i] == null ) {
                clienti[i] = aux;
                break;
            }
        */
        clientdb.insert();
    }

    public void stergeClient() {
        System.out.println("ID Client: ");
        int id = scanner.nextInt();
        clientdb.delete(id);
    }

    public void vindeMasina() {
        /*System.out.println("Index masina: ");
        int index = scanner.nextInt();
        scanner.nextLine();
        
        System.out.println("Index client: ");
        int index_client = scanner.nextInt();
        scanner.nextLine();
        
        Masina aux = minv.pop(index);
        clienti[index_client].setVIP(true);
        port.tranzactie( aux.getPret() ); */
        System.out.println("ID Masina: ");
        int id = scanner.nextInt();
        masinadb.delete(id);
    }

    public void vindePart() {
        /*System.out.println("Index: ");
        int index = scanner.nextInt();
        scanner.nextLine();
        Part aux = pinv.pop(index);
        port.tranzactie( aux.getPret() );*/
        System.out.println("ID: ");
        int id = scanner.nextInt();
        partdb.delete(id);
    }

    public void scrapMasina() {
        /*System.out.println("Index masina: ");
        int index = scanner.nextInt();
        scanner.nextLine();

        Masina m = minv.getMasini()[index];
        if( m != null ) {
            pinv.adauga(m.getSasiu());
            pinv.adauga(m.getRoti());
            pinv.adauga(m.getMotor());
            minv.pop(index);*/
        System.out.println("ID Masina: ");
        int id = scanner.nextInt();
        masinadb.scrap(id);
        }

    public void setPretMasina() {
        System.out.println("ID Masina: ");
        int id = scanner.nextInt();
        System.out.println("Pret Nou: ");
        int val = scanner.nextInt();
        masinadb.setPret(val, id);
        }
    }