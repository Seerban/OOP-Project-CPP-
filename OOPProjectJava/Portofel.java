public class Portofel {
    private int balance;
    private int[] istoric;
    private int istoric_counter;

    public Portofel(int bal) {
        this.balance = bal;
        this.istoric = new int[1000];
        this.istoric_counter = 1;
    }

    public int getBalance() {
        return balance;
    }

    public void tranzactie(int val) {
        balance += val;
        istoric[ istoric_counter ] = balance;
        istoric_counter++;
    }

    public void view() {
        System.out.println( "Balanta: " + balance);
        System.out.println("Istoric: ");
        for(int i=0; i<istoric_counter; i++)
            System.out.println(istoric[i]);
        }
}