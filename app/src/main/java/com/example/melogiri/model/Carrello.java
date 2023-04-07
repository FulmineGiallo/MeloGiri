package com.example.melogiri.model;

import java.util.List;

public class Carrello
{
    List<Bevanda> bevande;
    private int quantità;
    private Ordine ordine;

    public Carrello(List<Bevanda> bevande, int quantità, Ordine ordine)
    {
        this.bevande = bevande;
        this.quantità = quantità;
        this.ordine = ordine;
    }

    public List<Bevanda> getBevande()
    {
        return bevande;
    }

    public void setBevande(List<Bevanda> bevande)
    {
        this.bevande = bevande;
    }

    public int getQuantità()
    {
        return quantità;
    }

    public void setQuantità(int quantità)
    {
        this.quantità = quantità;
    }

    public Ordine getOrdine()
    {
        return ordine;
    }

    public void setOrdine(Ordine ordine)
    {
        this.ordine = ordine;
    }
}
