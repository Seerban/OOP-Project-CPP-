public class Masina {
    String nume;
    Part sasiu;
    Part roti;
    Part motor;
    int pret;

    public Masina(String nume, Part sasiu, Part roti, Part motor, int pret) {
        //if( sasiu.getCategorie() != Part.Categorie.Sasiu || roti.getCategorie() != Part.Categorie.Roti || motor.getCategorie() != Part.Categorie.Motor )
        //    throw new IllegalArgumentException("Invalid");
        this.nume = nume;
        this.sasiu = sasiu;
        this.roti = roti;
        this.motor = motor;
        this.pret = pret;
    }

    public Part getSasiu() {
        return sasiu;
    }

    public Part getRoti() {
        return roti;
    }

    public Part getMotor() {
        return motor;
    }

    public int getPret() {
        return pret;
    }

    @Override
    public String toString() {
        return nume + " $" + pret;
    }
}