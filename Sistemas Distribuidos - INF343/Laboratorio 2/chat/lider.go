package chat

import (
	"log"
	"math/rand"
	"math"
	"time"
	"golang.org/x/net/context"
	"fmt"
	"strconv"
)

type Server struct {
}

var jugadoresTotales int = 0
var jugadorActual int = 0
//Variables que tendrán las jugadas de los jugadores
var jugadasJugador1 string = ""
var jugadasJugador2 string = ""
var jugadasJugador3 string = ""
var jugadasJugador4 string = ""
var jugadasJugador5 string = ""
var jugadasJugador6 string = ""
var jugadasJugador7 string = ""
var jugadasJugador8 string = ""
var jugadasJugador9 string = ""
var jugadasJugador10 string = ""
var jugadasJugador11 string = ""
var jugadasJugador12 string = ""
var jugadasJugador13 string = ""
var jugadasJugador14 string = ""
var jugadasJugador15 string = ""
var jugadasJugador16 string = ""


var jugadores [16] int
var grupo1 [8] int
var sumaGrupo1 int = 0
var grupo2 [8] int
var sumaGrupo2 int = 0
var finJuego int = 0

var grupo1Etapa3[2] int
var grupo2Etapa3[2] int
var grupo3Etapa3[2] int
var grupo4Etapa3[2] int
var grupo5Etapa3[2] int
var grupo6Etapa3[2] int
var grupo7Etapa3[2] int
var grupo8Etapa3[2] int

var grupo1Gana bool
var grupo2Gana bool

var arreglarGrupo bool = true;

var LosGanadores string = ""
var rondaActual int = 0

func numeroAleatorio(valorMin int, valorMax int) int {
	rand.Seed(time.Now().UTC().UnixNano())
	return valorMin+rand.Intn(valorMax-valorMin)
}

func (s *Server) Bienvenida(ctx context.Context, msg *MensajeBienvenida) (*MensajeBienvenida, error) {
	peticion := msg.Body
	value := ""
	id := 1
	fmt.Println("Dejar entrar al jugador ID: ", jugadorActual, "\n [1] SI \n [2] NO")
	fmt.Scan(&value)
	switch peticion {
		case "1":
			id = jugadorActual
			jugadores[id] = 1
			jugadorActual += 1
			jugadoresTotales += 1
			if (value == "2"){
				jugadorActual-= 1
				jugadoresTotales-= 1
				jugadores[id] = 0
				id = jugadorActual
			}
	}
	return &MensajeBienvenida{Body: value, Id: int32(id)}, nil
}

func (s *Server) EntreEtapas(ctx context.Context, msg *MensajeEntreEtapas) (*MensajeEntreEtapas, error) {
	peticion := msg.Body
	value := ""
	switch peticion {
		case "1":
			fmt.Printf("Ingrese 'comenzar' para iniciar la siguiente etapa: ")
			fmt.Scan(&value)
			value = "Se da por iniciada la etapa"
			rondaActual += 1
			/*
			El jugador puede pasar a la siguiente etapa
			*/
		case "2":
			fmt.Println("Petición recibida para mostrar el pozo")
			value = "El pozo es: " + strconv.Itoa((16-jugadoresTotales)*100000000)
			/*
			Comunicación al pozo para recibir información y luego devolverla
			*/
	}
	return &MensajeEntreEtapas{Body: value}, nil
}

func (s *Server) MostrarGanador(ctx context.Context, msg *MensajeGanador) (*MensajeGanador, error) {
	if (jugadoresTotales == 1){
		fmt.Println("--------------------------------------------")
		fmt.Println("- EL jugador: "+ strconv.Itoa(int(msg.Id))+" ha ganado el Squid-Game    -")
		fmt.Println("--------------------------------------------")
		fmt.Println("")
		return &MensajeGanador{Id: msg.Id}, nil
	}

	return &MensajeGanador{Id: msg.Id}, nil
}

func (s *Server) EntreEtapas0(ctx context.Context, msg *MensajeEntreEtapas) (*MensajeEntreEtapas, error) {
	peticion := msg.Body
	value := ""
	decision := ""
	if (jugadoresTotales == 1){
		fmt.Println("--------------------------------------------")
		fmt.Println("- EL jugador: "+ strconv.Itoa(int(msg.Id))+" ha ganado el Squid-Game    -")
		fmt.Println("--------------------------------------------")
		fmt.Println("")
		return &MensajeEntreEtapas{Body: value}, nil
	}
	switch peticion {
		case "1":
			fmt.Printf("Ingrese: \n [x] Para ver las jugadas del jugador X \n [comenzar] Para comenzar la siguiente etapa")
			fmt.Scan(&decision)
			switch decision {
				case "comenzar":
					value = "Se da por iniciada la etapa"
				case "1":
					fmt.Println("Las jugadas del jugador 1 son: ")
					fmt.Println(jugadasJugador1)
				case "2":
					fmt.Println("Las jugadas del jugador 2 son: ")
					fmt.Println(jugadasJugador2)
				case "3":
					fmt.Println("Las jugadas del jugador 3 son: ")
					fmt.Println(jugadasJugador3)
				case "4":
					fmt.Println("Las jugadas del jugador 4 son: ")
					fmt.Println(jugadasJugador4)
				case "5":
					fmt.Println("Las jugadas del jugador 5 son: ")
					fmt.Println(jugadasJugador5)
				case "6":
					fmt.Println("Las jugadas del jugador 6 son: ")
					fmt.Println(jugadasJugador6)
				case "7":
					fmt.Println("Las jugadas del jugador 7 son: ")
					fmt.Println(jugadasJugador7)
				case "8":
					fmt.Println("Las jugadas del jugador 8 son: ")
					fmt.Println(jugadasJugador8)
				case "9":
					fmt.Println("Las jugadas del jugador 9 son: ")
					fmt.Println(jugadasJugador9)
				case "10":
					fmt.Println("Las jugadas del jugador 10 son: ")
					fmt.Println(jugadasJugador10)
				case "11":
					fmt.Println("Las jugadas del jugador 11 son: ")
					fmt.Println(jugadasJugador11)
				case "12":
					fmt.Println("Las jugadas del jugador 12 son: ")
					fmt.Println(jugadasJugador12)
				case "13":
					fmt.Println("Las jugadas del jugador 13 son: ")
					fmt.Println(jugadasJugador13)
				case "14":
					fmt.Println("Las jugadas del jugador 14 son: ")
					fmt.Println(jugadasJugador14)
				case "15":
					fmt.Println("Las jugadas del jugador 15 son: ")
					fmt.Println(jugadasJugador15)
				case "16":
					fmt.Println("Las jugadas del jugador 16 son: ")
					fmt.Println(jugadasJugador16)
			}
			/*
			El jugador puede pasar a la siguiente etapa
			*/
		case "2":
			log.Printf("Petición recibida: %s", msg.Body)
			value = "Puedes ver el pozo"
			/*
			Comunicación al pozo para recibir información y luego devolverla
			*/
	}
	return &MensajeEntreEtapas{Body: value}, nil
}
func (s *Server) Etapa1(ctx context.Context, msg *MensajeEtapa1) (*MensajeEtapa1, error) {
	numeroJugador := int(msg.Body)
	//Para dejar en visto las jugadas de cada jugador
	if (msg.Id == int32(0)){
		jugadasJugador1 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(1)){
		jugadasJugador2 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(2)){
		jugadasJugador3 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(3)){
		jugadasJugador4 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(4)){
		jugadasJugador5 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(5)){
		jugadasJugador6 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(6)){
		jugadasJugador7 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(7)){
		jugadasJugador8 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(8)){
		jugadasJugador9 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(9)){
		jugadasJugador10 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(10)){
		jugadasJugador11 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(11)){
		jugadasJugador12 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(12)){
		jugadasJugador13 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(13)){
		jugadasJugador14 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(14)){
		jugadasJugador15 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	if (msg.Id == int32(15)){
		jugadasJugador16 += "Etapa1 - Distancia recorrida: "+strconv.Itoa(int(msg.Body))+"\n"
	}
	value := 0
	numeroLider := numeroAleatorio(6, 10)
	log.Printf("Numero elegido por el Lider: %d", numeroLider)

	fmt.Println("-------------------------------------------------------")
	if numeroJugador >= numeroLider {
		//El jugador es eliminado, por lo que se debe actualizar el pozo
		log.Printf("Se ha eliminado un jugador")
		value = -1
		jugadoresTotales = jugadoresTotales -1
		jugadores[int(msg.Id)] = 0
	}
	if (jugadoresTotales == 0){
		finJuego = -1
	}
	if (jugadoresTotales == 1){
		finJuego = 1
	}
	fmt.Println("Los jugadores que quedan son: ", jugadoresTotales)
	fmt.Println(jugadores)
	fmt.Println("-------------------------------------------------------")
	return &MensajeEtapa1{Body: int32(value), FinJuego: int32(finJuego)}, nil
}

func (s *Server) InicioEtapa2(ctx context.Context, msg *MensajeEtapa2) (*MensajeEtapa2, error) {
	Value := int32(0)
	if ((jugadoresTotales%2==0 || jugadoresTotales==1)&& arreglarGrupo) {
		arreglarGrupo = false;
		tocaG1 := true
		tocaG2 := false
		contador1 := 0
		contador2 := 0
		for i := 0; i <= 15; i++ {
			if (jugadores[i] == 1){
				if (tocaG1){
					grupo1[contador1] = i
					contador1++
					tocaG1 = false
					tocaG2 = true
				}
				if (tocaG2){
					grupo2[contador2] = i
					contador2++
					tocaG1 = true
					tocaG2 = false
				}
			}
		}
		fmt.Println("Los equipos han sido elegidos")

	}
	for i := 0; i <= 7; i++ {
		if (msg.Id == int32(grupo1[i])){
			Value = int32(1)
		}else{
			Value = int32(2)
		}
	}
	return &MensajeEtapa2{Body: int32(1), Id: msg.Id, Group: Value}, nil
}

func (s *Server) Etapa3(ctx context.Context, msg *MensajeEtapa3) (*MensajeEtapa3, error) {
	if (jugadoresTotales%2 ==0){
		numeroLider := numeroAleatorio(1, 10)
		log.Printf("Numero elegido por el Lider: %d", numeroLider)
		log.Printf("Resta absoluta: ",math.Abs(float64(msg.Body)-float64(numeroLider)))
	}else{
		//Se debe eliminar uno al azar
		fmt.Println("Se ha eliminado un jugador al azar")
	}
	
	return &MensajeEtapa3{Body: int32(1)}, nil
}

func (s *Server) Etapa2(ctx context.Context, msg *MensajeEtapa2) (*MensajeEtapa2, error) {
	fmt.Println(msg.Group)
	if (msg.Group == int32(1)){
		sumaGrupo1 += int(msg.Valor)
		fmt.Println("La suma del grupo 1 es: ", sumaGrupo1)
	}else{
		sumaGrupo2 += int(msg.Valor)
		fmt.Println("La suma del grupo 2 es: ", sumaGrupo2)
	}
	numeroLider := numeroAleatorio(1, 4)
	log.Printf("Numero elegido por el Lider: %d", numeroLider)

	if (sumaGrupo1%2 == numeroLider%2){
		//El grupo 1 es el ganador
		grupo1Gana = true
	}
	if (sumaGrupo2%2 == numeroLider%2){
		//El grupo 2 es el ganador
		grupo2Gana = true
	}
	if (grupo1Gana && !grupo2Gana){
		//El grupo 1 gana
		fmt.Println("El grupo 1 gana")
		//Se elimina el grupo 2
		for i := 0; i <= 7; i++ {
			if (jugadores[grupo2[i]] == 1){
				jugadores[grupo2[i]] = 0
				jugadoresTotales = jugadoresTotales -1
				fmt.Println("Jugador: "+strconv.Itoa(grupo2[i])+" eliminado")
			}
		}
	}
	if (!grupo1Gana && grupo2Gana){
		//El grupo 2 gana
		fmt.Println("El grupo 2 gana")
		//Se elimina al grupo 1
		for i := 0; i <= 7; i++ {
			if (jugadores[grupo1[i]] == 1){
				jugadores[grupo1[i]] = 0
				jugadoresTotales = jugadoresTotales -1
				fmt.Println("Jugador: "+strconv.Itoa(grupo1[i])+" eliminado")
			}
		}
	}

	if ( grupo1Gana && grupo2Gana){
		//Los dos equipoas ganas
		fmt.Println("Los dos equipos pueden pasar")
		//Los dos equipos pasan
	}

	if (!grupo1Gana && !grupo2Gana){
		//No hay ganador
		fmt.Println("No hay ganador, se eliminará un equipo al azar")
		//Se elige al azar
		equipoEliminado := numeroAleatorio(1, 2)
		if (equipoEliminado == 1){
			//Se elimina el grupo 1
			for i := 0; i <= 7; i++ {
				if (jugadores[grupo1[i]] == 1){
					jugadores[grupo1[i]] = 0
					jugadoresTotales = jugadoresTotales -1
					fmt.Println("Jugador: "+strconv.Itoa(grupo1[i])+" eliminado")
				}
			}
		}else{
			//Se elimina el grupo 2
			for i := 0; i <= 7; i++ {
				if (jugadores[grupo2[i]] == 1){
					jugadores[grupo2[i]] = 0
					jugadoresTotales = jugadoresTotales -1
					fmt.Println("Jugador: "+strconv.Itoa(grupo2[i])+" eliminado")
				}
			}
		}
	}
	fmt.Println("-------------------------------------------------------")
	fmt.Println("Los jugadores que quedan son: ", jugadoresTotales)
	fmt.Println("Los jugadores vivos se muestran con un 1 en su posición")
	fmt.Println(jugadores)
	fmt.Println("-------------------------------------------------------")

	if (jugadoresTotales == 0){
		finJuego = -1
	}
	if (jugadoresTotales == 1){
		finJuego = 1
	}

	return &MensajeEtapa2{Body: int32(0), FinJuego: int32(finJuego)}, nil

} 