public class PartInventar extends Inventar {
    private Part[] parti;

    public PartInventar(int len) {
        super(len);
        this.parti = new Part[len];
    }
    
    public Part[] getParti() {
        return parti;
    }

    public void show() {
        System.out.println( "Capacitate: " + getCapacitate() );
        System.out.println( "Cantitate: " + getCantitate() );
        for(int i=0; i<getCapacitate(); ++i) if (parti[i] != null) System.out.println("(" + i + ") " + parti[i]);
    }

    public void adauga(Part p) {
        setCantitate( getCantitate() + 1 );
        for(int i=0; i<getCantitate(); i++)
            if( parti[i] == null ) {
                parti[i] = p;
                return;
            }
    }

    public Part pop(int index) {
        Part aux = parti[index];
        if( aux != null ) setCantitate( getCantitate() - 1 );
        parti[index] = null;
        return aux;
    }
}