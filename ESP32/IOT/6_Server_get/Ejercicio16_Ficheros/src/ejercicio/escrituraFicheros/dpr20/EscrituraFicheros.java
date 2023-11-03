package ejercicio.escrituraFicheros.dpr20;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class EscrituraFicheros {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		String nombre, apellido, telef, ficha;
				
		InputStreamReader lectBits = new InputStreamReader(System.in);	//lectBits es de clase InputStreamReader y recibe los valores de System.in (Lee el teclado) 
		BufferedReader lnscan = new BufferedReader(lectBits);	//almacena los valores y les da formato de string a lo que lee, en este caso a Input... que es la lectura del teclado
		File datos = new File("Datos.txt");
		//fichero.createNewFile();
		FileWriter escribir =new FileWriter(datos);
		
		System.out.println("Escriba su nombre");
		nombre=lnscan.readLine();
		System.out.println("Escriba su apellido");
		apellido=lnscan.readLine();
		System.out.println("Escriba su numero de telefono");
		telef=lnscan.readLine();
		
		ficha= nombre+" "+apellido+" "+telef+"\n";
		lnscan.close();

		System.out.println(ficha);
		
		escribir.write(ficha);
		escribir.close();

	}

}
