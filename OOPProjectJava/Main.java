import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] cmds = {"1. Vezi Buget",
                        "2. Vezi Masini",
                        "3. Vezi Parti",
                        "4. Vezi Clienti",
                        "5. Creeaza Parte",
                        "6. Creeaza Masina",
                        "7. Adauga Client",
                        "8. Vinde Masina",
                        "9. Vinde Part",
                        "10. Scrap",
                        "11. Exit"
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
                    case 1 ->   service.showBal();
                    case 2 ->   service.veziMasini();
                    case 3 ->   service.veziPart();
                    case 4 ->   service.veziClienti();
                    case 5 ->   service.adaugaPart();
                    case 6 ->   service.adaugaMasina();
                    case 7 ->   service.adaugaClient();
                    case 8 ->   service.vindeMasina();
                    case 9 ->   service.vindePart();
                    case 10 ->  service.scrapMasina();
                    case 11 ->  exit = true;
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