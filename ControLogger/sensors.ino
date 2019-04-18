
// WATER LEVEL SENSOR ****************************************************************************************************************************

bool getSensorMin(){                                // Función que lee el sensor de nivel de agua inferior.
  FCN
  int i;
  int valido = 0;
  int measure;
  for (i = 0; i < controlMin; i++){                 // Hace "controlMin" lecturas para asegurarse de que no hay falsas señales que puedan activar la bomba.
    measure = analogRead(SENSOR_MIN);               // Lee la señal en el pin SENSOR_MIN.
    if (measure SENSOR_HIGH limitMin) valido++;     // Si es mayor/menor que el límite configurado (cambiar modo en "Controller"), anota la lectura como válida.
    delayMicroseconds(100);                         // Deja un intervalo de tiempo entre lecturas para que la señal se estabilice.
  }
  DEBUG(measure)
  DEBUG(valido)
  if (valido == controlMin) return 1;               // Si todas las lecturas han dado el mismo resultado satisfactorio,
  else return 0;                                    // entonces confirma que el nivel de agua está por encima del sensor.
}

bool getSensorMax(){                                // Mismo algoritmo que "getSensorMin()", pero para el sensor de nivel de agua superior.
  FCN
  int i;
  int valido = 0;
  int measure;
  for (i=0; i < controlMax; i++){
    measure = analogRead(SENSOR_MAX);
    //Serial.println(measure);
    if (measure SENSOR_HIGH limitMax) valido++;
    delayMicroseconds(100);
  }
  DEBUG(measure)
  DEBUG(valido)
  if (valido == controlMax) return 1;
  else return 0;
}

void getSensors(){                                  // Función que asigna a la variable waterLevel el estado del depósito.
  FCN
  if (getSensorMax()) {                             // Si la función "getSensorMax()" da positivo, el agua está por encima del sensor superior.
    waterLevel = overMax;
    if (serial) Serial.println("OVER MAX");
  }
  else if(getSensorMin()) {                         // En caso contrario, si la función "getSensorMin()" da positivo, 
    waterLevel = midLevel;                          // el agua está por encima del sensor inferior, pero por debajo del superior: está a media altura.
    if(serial) Serial.println("MIDDLE LEVEL");
  }
  else {                                            // Si no es ninguno de los casos anteriores, no queda más remedio que el bidón esté vacío y haya que rellenarlo.
    waterLevel = underMin;
    if(serial) Serial.println("UNDER MIN");
  }
}

