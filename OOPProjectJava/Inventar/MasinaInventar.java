public class MasinaInventar extends Inventar {
    private Masina[] masini;

    public MasinaInventar(int len) {
        super(len);
        this.masini = new Masina[len];
    }
    
    public Masina[] getMasini() {
        return masini;
    }

    public void show() {
        System.out.println( "Capacitate: " + getCapacitate() );
        System.out.println( "Cantitate: " + getCantitate() );
        for(int i=0; i<getCapacitate(); ++i) if (masini[i] != null) System.out.println("(" + i + ") " + masini[i]);
    }

    public void adauga(Masina m) {
        setCantitate( getCantitate() + 1 );
        for(int i=0; i<getCantitate(); i++)
            if( masini[i] == null ) {
                masini[i] = m;
                return;
            }
    }

    public Masina pop(int index) {
        Masina aux = masini[index];
        if( aux != null ) setCantitate( getCantitate() - 1 );
        masini[index] = null;
        return aux;
    }
}