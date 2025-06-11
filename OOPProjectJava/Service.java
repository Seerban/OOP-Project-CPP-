import java.util.Scanner;

public class Service {
    Portofel port;
    PartInventar pinv;
    MasinaInventar minv;
    Client[] clienti;

    Scanner scanner;
    
    public Service(Scanner in) {
        port = new Portofel(0);
        pinv = new PartInventar(20);
        minv = new MasinaInventar(20);
        clienti = new Client[20];
        this.scanner = in;
    }
    
    public void showBal() {
        port.view();
    }

    public void veziPart() {
        pinv.show();
    }

    public void veziMasini() {
        minv.show();
    }

    public void veziClienti() {
        for(int i=0; i<clienti.length; ++i)
            if( clienti[i] != null )
                System.out.println(clienti[i]);
    }

    public void adaugaMasina() {
        System.out.println("Adauga Masina:");
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
        minv.adauga(masina);
    }   

    public void adaugaPart() {
        System.out.println("Adauga part: ( nume, pret, an, categorie(Motor/Roti/Sasiu) )");
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
        pinv.adauga(p);
    }

    public void adaugaClient() {
        System.out.println("Nume: ");
        String nume = scanner.next();
        Client aux = new Client(nume);
        for(int i=0; i < clienti.length; ++i) 
            if( clienti[i] == null ) {
                clienti[i] = aux;
                break;
            }
    }

    public void vindeMasina() {
        System.out.println("Index masina: ");
        int index = scanner.nextInt();
        scanner.nextLine();
        
        System.out.println("Index client: ");
        int index_client = scanner.nextInt();
        scanner.nextLine();
        
        Masina aux = minv.pop(index);
        clienti[index_client].setVIP(true);
        port.tranzactie( aux.getPret() );
    }

    public void vindePart() {
        System.out.println("Index: ");
        int index = scanner.nextInt();
        scanner.nextLine();
        Part aux = pinv.pop(index);
        port.tranzactie( aux.getPret() );
    }

    public void scrapMasina() {
        System.out.println("Index masina: ");
        int index = scanner.nextInt();
        scanner.nextLine();

        Masina m = minv.getMasini()[index];
        if( m != null ) {
            pinv.adauga(m.getSasiu());
            pinv.adauga(m.getRoti());
            pinv.adauga(m.getMotor());
            minv.pop(index);
        }
    }
}