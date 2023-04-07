package com.example.melogiri.model;

import java.util.Date;
import java.util.List;

public class Utente
{
    private String nome;
    private String cognome;
    private Date data;
    private String email;
    private String password;
    private List<Ordine> ordini;

    public Utente(String nome, String cognome, Date data, String email, String password, List<Ordine> ordini)
    {
        this.nome = nome;
        this.cognome = cognome;
        this.data = data;
        this.email = email;
        this.password = password;
        this.ordini = ordini;
    }

    public String getNome()
    {
        return nome;
    }
    public void setNome(String nome)
    {
        this.nome = nome;
    }
    public String getCognome()
    {
        return cognome;
    }
    public void setCognome(String cognome)
    {
        this.cognome = cognome;
    }
    public Date getData()
    {
        return data;
    }
    public void setData(Date data)
    {
        this.data = data;
    }
    public String getEmail()
    {
        return email;
    }
    public void setEmail(String email)
    {
        this.email = email;
    }
    public String getPassword()
    {
        return password;
    }
    public void setPassword(String password)
    {
        this.password = password;
    }
    public List<Ordine> getOrdini()
    {
        return ordini;
    }
    public void setOrdini(List<Ordine> ordini)
    {
        this.ordini = ordini;
    }
}
