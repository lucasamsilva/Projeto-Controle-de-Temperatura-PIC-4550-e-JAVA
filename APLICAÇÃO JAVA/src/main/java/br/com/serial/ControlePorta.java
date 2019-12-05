
package br.com.serial;

import com.sun.javafx.fxml.expression.BinaryExpression;
import com.sun.management.jmx.Trace;
import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import java.io.IOException;
import java.io.OutputStream;
import javax.swing.JOptionPane;

import java.io.InputStream;

public class ControlePorta {

    private OutputStream serialOut;
    private InputStream serialIn;
    private int taxa;
    private String portaCOM;

    public int getTaxa() {
        return taxa;
    }

    public void setTaxa(int taxa) {
        this.taxa = taxa;
    }

    public String getPortaCOM() {
        return portaCOM;
    }

    /**
     * Construtor da classe ControlePorta
     *
     * @param portaCOM - Porta COM que será utilizada para enviar os dados para
     * o arduino
     * @param taxa - Taxa de transferência da porta serial geralmente é 9600
     */
    public void setPortaCOM(String portaCOM) {
        this.portaCOM = portaCOM;
    }

    /**
     * Médoto que verifica se a comunicação com a porta serial está ok
     */
    public boolean initialize() {
        try {
            //Define uma variável portId do tipo CommPortIdentifier para realizar a comunicação serial
            CommPortIdentifier portId = null;
            try {
                //Tenta verificar se a porta COM informada existe
                portId = CommPortIdentifier.getPortIdentifier(this.portaCOM);
            } catch (NoSuchPortException npe) {
                //Caso a porta COM não exista será exibido um erro 
                JOptionPane.showMessageDialog(null, "Porta COM não encontrada.",
                        "Porta COM", JOptionPane.PLAIN_MESSAGE);
                        return false;
            }
            //Abre a porta COM 
            SerialPort port = (SerialPort) portId.open("Comunicação serial", this.taxa);
            serialOut = port.getOutputStream();
            serialIn = port.getInputStream();
            port.setSerialPortParams(this.taxa, //taxa de transferência da porta serial 
                    SerialPort.DATABITS_8, //taxa de 10 bits 8 (envio)
                    SerialPort.STOPBITS_1, //taxa de 10 bits 1 (recebimento)
                    SerialPort.PARITY_NONE); //receber e enviar dados
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Método que fecha a comunicação com a porta serial
     */
    public void close() {
        try {
            serialOut.close();
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Não foi possível fechar porta COM.",
                    "Fechar porta COM", JOptionPane.PLAIN_MESSAGE);
        }
    }
    
    public String recebeDados(int comando){
        char dados = 0;
        String print = new String();
        enviaDados(comando);
        try {
            
            for (int i =0; i<10;i++){
                dados = (char) serialIn.read();
                if(Character.isDigit(dados) || dados == '.'){
                print += dados;}
            }
            return print;
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "Não foi possível receber o dado. ",
                    "Receber dados", JOptionPane.PLAIN_MESSAGE);
                return null;
        }
    }

    /**
     * @param opcao - Valor a ser enviado pela porta serial
     */
    public void enviaDados(int opcao) {
        try {
           serialOut.write(opcao);//escreve o valor na porta serial para ser enviado
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "Não foi possível enviar o dado. ",
                    "Enviar dados", JOptionPane.PLAIN_MESSAGE);
        }
    }
}

