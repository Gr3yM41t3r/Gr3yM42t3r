import { Component, OnDestroy } from "@angular/core";
import { NbThemeService } from "@nebular/theme";
import {
  Temperature,
  TemperatureHumidityData,
} from "../../../@core/data/temperature-humidity";
import { takeWhile } from "rxjs/operators";
import { forkJoin, Observable } from "rxjs";
import { HttpClient } from "@angular/common/http";
import { electricity } from "../../../models/electricity";
import { NbIconLibraries } from "@nebular/theme";

@Component({
  selector: "ngx-temperature",
  styleUrls: ["./temperature.component.scss"],
  templateUrl: "./temperature.component.html",
})
export class TemperatureComponent implements OnDestroy {
  private alive = true;

  temperatureData: Temperature;
  temperature: number;
  temperatureOff = false;
  temperatureMode = "cool";

  humidityData: Temperature;
  humidity: number;
  humidityOff = false;
  humidityMode = "heat";

  ElectricityData: Temperature;
  electricity: number = 235;
  min: number = 0;
  max: number = 270;
  electricityOff = false;
  electricityMode = "volts";
  electricityText = "volts";
  currentDisplay: string = "volts";

  theme: any;
  themeSubscription: any;
  seconds: number = 60;

  readonly ROOT_URL = "http://127.0.0.1:5000/";

  electricityReading: electricity;
  evaIcons = [];

  constructor(
    private themeService: NbThemeService,
    private temperatureHumidityService: TemperatureHumidityData,
    private http: HttpClient,
    iconsLibrary: NbIconLibraries
  ) {
    this.evaIcons = Array.from(iconsLibrary.getPack("eva").icons.keys()).filter(
      (icon) => icon.indexOf("outline") === -1
    );

    iconsLibrary.registerFontPack("fa", {
      packClass: "fa",
      iconClassPrefix: "fa",
    });
    iconsLibrary.registerFontPack("far", {
      packClass: "far",
      iconClassPrefix: "fa",
    });
    iconsLibrary.registerFontPack("ion", { iconClassPrefix: "ion" });

    this.getLatestReading();
    this.themeService
      .getJsTheme()
      .pipe(takeWhile(() => this.alive))
      .subscribe((config) => {
        this.theme = config.variables.temperature;
      });

    forkJoin(
      this.temperatureHumidityService.getTemperatureData(),
      this.temperatureHumidityService.getHumidityData()
    ).subscribe(
      ([temperatureData, humidityData]: [Temperature, Temperature]) => {
        this.temperatureData = temperatureData;
        this.temperature = this.temperatureData.value;

        this.humidityData = humidityData;
        this.humidity = this.humidityData.value;
      }
    );

    setInterval(() => {
      this.getLatestReading();
    }, this.seconds * 1000);
  }

  getLatestReading() {
    this.http
      .get<electricity>(this.ROOT_URL + "readlatest")
      .subscribe((res) => {
        this.electricityReading = res;
        this.refreshReading(this.currentDisplay);
      });
      
  }

  radioChange(event: Event) {
    this.currentDisplay = String(event);
    this.refreshReading(this.currentDisplay);
  }
  refreshReading(measure: string) {
    if (measure == "volts") {
      this.max = 270;
      this.min = 0;
      this.electricityText = "volts";
      this.electricity = this.electricityReading.voltage;
    } else if (measure == "current") {
      this.max = 15;
      this.min = 0;
      this.electricityText = "ampere";
      this.electricity = this.electricityReading.current;
    } else if (measure == "power") {
      this.max = 6000;
      this.min = 0;
      this.electricityText = "Watt";
      this.electricity = this.electricityReading.power;
    } else if (measure == "energy") {
      this.max = 400;
      this.min = 0;
      this.electricityText = "KWh";
      this.electricity = this.electricityReading.energy;
    } else if (measure == "frequency") {
      this.max = 51;
      this.min = 49;
      this.electricityText = "Hz";
      this.electricity = this.electricityReading.frequency;
    } else if (measure == "powerfactor") {
      this.max = 1;
      this.min = 0;
      this.electricityText = "";
      this.electricity = this.electricityReading.power_factor;
    }
  }

  ngOnDestroy() {
    this.alive = false;
  }
}
