public class Part {
    public enum Categorie {
        Motor, Roti, Sasiu
    }
    private String nume;
    private int pret;
    private int an;
    private Categorie categorie;

    public Part(String nume, int pret, int an, Categorie cat) {
        this.nume = nume;
        this.pret = pret;
        this.an = an;
        this.categorie = cat;
    }

    public String getNume() {
        return nume;
    }

    public int getPret() {
        return pret;
    }

    public int getAn() {
        return an;
    }

    public Categorie getCategorie() {
        return categorie;
    }

    @Override
    public String toString() {
        return "(" + categorie + ") " + nume + " " + an + " $" + pret;
    }
}