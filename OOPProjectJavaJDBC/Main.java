import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] cmds = {
                        "11. Vezi Buget",
                        "12. Tranzactie",
                        "21. Vezi Masini",
                        "22. Creeaza Masina",
                        "23. Vinde Masina",
                        "24. Scrap",
                        "25. Schimba Pret Masina",
                        "31. Vezi Parti",
                        "32. Creeaza Part",
                        "33. Vinde Part",
                        "41. Vezi Clienti",
                        "42. Adauga Client",
                        "43. Sterge Client",
                        "0. Exit"
                    };

        Service service = new Service(scanner);
        boolean exit = false;
        while(!exit) {
            try {
                System.out.println("\n\n");
                for (String s : cmds) { 
                    System.out.println( s );
                    }

                int x;
                x = scanner.nextInt();
                scanner.nextLine();
                switch(x) {
                    case 11 ->  service.showBal();
                    case 12 ->  service.tranzactie();
                    case 21 ->  service.veziMasini();
                    case 22 ->  service.adaugaMasina();
                    case 23 ->  service.vindeMasina();
                    case 24 ->  service.scrapMasina();
                    case 25 ->  service.setPretMasina();
                    case 31 ->  service.veziPart();
                    case 32 ->  service.adaugaPart();
                    case 33 ->  service.vindePart();
                    case 41 ->  service.veziClienti();
                    case 42 ->  service.adaugaClient();
                    case 43 ->  service.stergeClient();
                    case 0 ->   exit = true;
                    default ->  System.out.println("Invalid");
                }

            System.out.println("1 pt a continua.");
            if (x != 11) scanner.nextLine(); //asteapta input pt a continua
        } catch (Exception e) {
            System.out.println("Input invalid");
            if( scanner.hasNextLine()) scanner.nextLine();
        }
    }
    scanner.close();
    }
}