/**
 * Projetos Arduino
 * 
 * @author diego patriota
 * @link https://github.com/diegopatriota
 * 19/05/2016 
 */

//----(Bibliotecas)------------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>
#include <Ultrasonic.h>

//----(Declaração de variáveis)------------------------------------------------------------------------------
 
//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(169,254,158,247);          //Define o endereco IP
IPAddress gateway(192,168,1,1);      //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);

Ultrasonic ultrasonic(3,4); // Alterar pino de acordo com as portas utilizadas no arduino
//Declaração das constantes referentes aos pinos digitais.
const int ledVerde = 13;

long microsec = 0;
float distanciaCM = 0;


//----(Setup)-----------------------------------------------------------------------------------------
 
void setup()
{
  //Inicializa a interface de rede
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
    pinMode(ledVerde,OUTPUT); //10 como de saída.
}

//-----(Funções)---(Inicio)---------------------------------------------------------------------------------- 
void loop() {
  
  //Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
        
    while (client.connected()) {
      if (client.available()) {
        
//---(Sensores)--(Inicio)-------------------------------------------------------------------------------------

      //Lendo o sensor
        microsec = ultrasonic.timing(); 
       
        //Convertendo a distância em CM
        distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM); 
          ledDistancia();
       
        


//---(Sensores)--(Fim)-------------------------------------------------------------------------------------------                
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          
//---(HTML)----(Início)---------------------------------------------------------------------------------------          
          
client.println("<!DOCTYPE html>       ");
client.println("<html>       ");
client.println("<head>       ");
client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />       ");
client.println("<title>Cronômetro Digital Online com Javascript</title>       ");
client.println("<style type='text/css'>       ");
client.println("*{       ");
client.println("	margin:0;       ");
client.println("	padding:0;       ");
client.println("	}       ");
client.println("body{       ");
client.println("	background:#CCC;       ");
client.println("	color:#FFF;       ");
client.println("	font-family:Arial, Helvetica, sans-serif;       ");
client.println("	text-align:center;       ");
client.println("	}       ");
client.println("#topo{       ");
client.println("	background:#069;       ");
client.println("	height:100px;       ");
client.println("	line-height:100px;       ");
client.println("	border-bottom:2px solid #006;       ");
client.println("	}       ");
client.println("h2 a{       ");
client.println("	color:#069;       ");
client.println("	text-decoration:none;       ");
client.println("	}       ");
client.println("h2 a:hover{       ");
client.println("	color:#006;       ");
client.println("	}       ");
client.println("input[type=text]{       ");
client.println("	text-align: center;       ");
client.println("	background:#ccc;       ");
client.println("	width:900px;       ");
client.println("	height:200px;       ");
client.println("	line-height:200px;       ");
client.println("	font-size:150px;       ");
client.println("	border:none;       ");
client.println("	}       ");
client.println("</style>       ");
client.println("<script language='JavaScript'>       ");
client.println("var timercount = 0;       ");
client.println("var timestart  = null;       ");
 
client.println("function showtimer() {       ");
client.println("	if(timercount) {       ");
client.println("		clearTimeout(timercount);       ");
client.println("		clockID = 0;       ");
client.println("	}       ");
client.println("	if(!timestart){       ");
client.println("		timestart = new Date();       ");
client.println("	}       ");
client.println("	var timeend = new Date();       ");
client.println("	var timedifference = timeend.getTime() - timestart.getTime();       ");
client.println("	timeend.setTime(timedifference);       ");
client.println("	var minutes_passed = timeend.getMinutes();       ");
client.println("	if(minutes_passed < 10){       ");
client.println("		minutes_passed = '0' + minutes_passed;       ");
client.println("	}       ");
client.println("	var seconds_passed = timeend.getSeconds();       ");
client.println("	if(seconds_passed < 10){       ");
client.println("		seconds_passed = '0' + seconds_passed;       ");
client.println("	}       ");

client.println("	var milliseconds_passed = timeend.getMilliseconds();       ");
client.println("		if(milliseconds_passed < 10){       ");
client.println("			milliseconds_passed = '00' + milliseconds_passed;       ");
client.println("		}       ");
client.println("		else if(milliseconds_passed < 100){       ");
client.println("			milliseconds_passed = '0' + milliseconds_passed;       ");
client.println("		}       ");
client.println("	document.timeform.timetextarea.value = minutes_passed + ':' + seconds_passed + '.' + milliseconds_passed;       ");
client.println("	timercount = setTimeout('showtimer()', 100);       ");
client.println("}       ");
 
client.println("function sw_start(){       ");
client.println("	if(!timercount){       ");
client.println("	timestart   = new Date();       ");
client.println("	document.timeform.timetextarea.value = '00:00.000';       ");
client.println("	document.timeform.laptime.value = '';       ");
client.println("	timercount  = setTimeout('showtimer()', 1000);       ");
client.println("	}       ");
client.println("	else{       ");
client.println("	var timeend = new Date();       ");
client.println("		var timedifference = timeend.getTime() - timestart.getTime();       ");
client.println("		timeend.setTime(timedifference);       ");
client.println("		var minutes_passed = timeend.getMinutes();       ");
client.println("		if(minutes_passed < 10){       ");
client.println("			minutes_passed = '0' + minutes_passed;       ");
client.println("		}       ");
client.println("		var seconds_passed = timeend.getSeconds();       ");
client.println("		if(seconds_passed < 10){       ");
client.println("			seconds_passed = '0' + seconds_passed;       ");
client.println("		}       ");
client.println("		var milliseconds_passed = timeend.getMilliseconds();       ");
client.println("		if(milliseconds_passed < 10){       ");
client.println("			milliseconds_passed = '00' + milliseconds_passed;       ");
client.println("		}       ");
client.println("		else if(milliseconds_passed < 100){       ");
client.println("			milliseconds_passed = '0' + milliseconds_passed;       ");
client.println("		}       ");
client.println("		document.timeform.laptime.value = minutes_passed + ':' + seconds_passed + '.' + milliseconds_passed;       ");
client.println("	}       ");
client.println("}       ");
        
client.println("function Stop() {       ");
client.println("	if(timercount) {       ");
client.println("		clearTimeout(timercount);       ");
client.println("		timercount  = 0;       ");
client.println("		var timeend = new Date();       ");
client.println("		var timedifference = timeend.getTime() - timestart.getTime();       ");
client.println("		timeend.setTime(timedifference);       ");
client.println("		var minutes_passed = timeend.getMinutes();       ");
client.println("		if(minutes_passed < 10){       ");
client.println("			minutes_passed = '0' + minutes_passed;       ");
client.println("		}       ");
client.println("		var seconds_passed = timeend.getSeconds();       ");
client.println("		if(seconds_passed < 10){       ");
client.println("			seconds_passed = '0' + seconds_passed;       ");
client.println("		}       ");
client.println("		var milliseconds_passed = timeend.getMilliseconds();       ");
client.println("		if(milliseconds_passed < 10){       ");
client.println("			milliseconds_passed = '00' + milliseconds_passed;       ");
client.println("		}       ");
client.println("		else if(milliseconds_passed < 100){       ");
client.println("			milliseconds_passed = '0' + milliseconds_passed;       ");
client.println("		}       ");
client.println("		document.timeform.timetextarea.value = minutes_passed + ':' + seconds_passed + '.' + milliseconds_passed;       ");
client.println("	}       ");
client.println("	timestart = null;       ");
client.println("}       ");
 
client.println("function Reset() {       ");
client.println("	timestart = null;       ");
client.println("	document.timeform.timetextarea.value = '00:00.000';       ");
client.println("	document.timeform.laptime.value = '';       ");
client.println("}       ");

client.println("</script>       ");


client.println("</head>       ");
client.println("<body>       ");
client.println("	<div id='topo'>       ");
client.println("    	<h1>Cronômetro Digital Online com Javascript</h1>       ");
client.println("    </div>       ");

client.println("    <form name='timeform'>       ");
client.println("		Time: <input type='text' name='timetextarea' value='00:00:000' size='10' /><br>        ");
client.println("		Lap: <input type='text' name='laptime' size='10' >       ");
client.println("		<br>       ");
client.println("		<input type='button' name='start' value='Start/Lap' onclick='sw_start()' >        ");
client.println("		<input type='button' name='stop' value='Stop' onclick='Stop()'>        ");
client.println("		<input type='button' name='reset' value='Reset' onclick='Reset()'>       ");
client.println("	</form>       ");
client.println("    <br />       ");
client.println("</body>       ");
client.println("</html>       ");
     
          
          
          break;
          
//---(HTML)--(fim)------------------------------------------------------------------------------------------                   
          
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }
}

//Método que centraliza o controle de acendimento dos leds.
void ledDistancia() {

  //Acendendo o led adequado para a distância lida no sensor
  if (distanciaCM < 120) {
       digitalWrite(ledVerde,HIGH);
     
  }else{
       digitalWrite(ledVerde,LOW);  
     
  }
   
}
//-----(Funções)---(Inicio)----------------------------------------------------------------------------------
