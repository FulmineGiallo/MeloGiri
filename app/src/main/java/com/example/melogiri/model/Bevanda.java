package com.example.melogiri.model;

public class Bevanda
{
    private String nome;
    private String urlPhoto;
    private int livelloAlcolico;
    private String descrizione;
    private Categoria categoria;
    private int prezzo;

    public Bevanda(String nome, String urlPhoto, int livelloAlcolico, String descrizione, Categoria categoria, int prezzo)
    {
        this.nome = nome;
        this.urlPhoto = urlPhoto;
        this.livelloAlcolico = livelloAlcolico;
        this.descrizione = descrizione;
        this.categoria = categoria;
        this.prezzo = prezzo;
    }

    public String getNome()
    {
        return nome;
    }
    public void setNome(String nome)
    {
        this.nome = nome;
    }

    public String getUrlPhoto()
    {
        return urlPhoto;
    }

    public void setUrlPhoto(String urlPhoto)
    {
        this.urlPhoto = urlPhoto;
    }

    public int getLivelloAlcolico()
    {
        return livelloAlcolico;
    }

    public void setLivelloAlcolico(int livelloAlcolico)
    {
        this.livelloAlcolico = livelloAlcolico;
    }

    public String getDescrizione()
    {
        return descrizione;
    }

    public void setDescrizione(String descrizione)
    {
        this.descrizione = descrizione;
    }

    public Categoria getCategoria()
    {
        return categoria;
    }

    public void setCategoria(Categoria categoria)
    {
        this.categoria = categoria;
    }

    public int getPrezzo()
    {
        return prezzo;
    }

    public void setPrezzo(int prezzo)
    {
        this.prezzo = prezzo;
    }
}
