import {Component, OnDestroy} from '@angular/core';
import { NbThemeService } from '@nebular/theme';
import { takeWhile } from 'rxjs/operators' ;
import { SolarData } from '../../@core/data/solar';

interface CardSettings {
  title: string;
  iconClass: string;
  type: string;
  src:string;
}

@Component({
  selector: 'ngx-dashboard',
  styleUrls: ['./dashboard.component.scss'],
  templateUrl: './dashboard.component.html',
})
export class DashboardComponent implements OnDestroy {

  private alive = true;

  solarValue: number;

  mainDoor: CardSettings = {
    title: 'Porte Principale',
    iconClass: 'nb-lightbulb',
    type: 'primary',
    src: 'assets/icons/open-door.png',
  };
  rollerShadesCard: CardSettings = {
    title: 'Rideaux',
    iconClass: 'nb-roller-shades',
    type: 'success',
    src: 'assets/icons/shade.png',
    
  };
  garage: CardSettings = {
    title: 'Garage',
    iconClass: 'nb-audio',
    type: 'info',
    src: 'assets/icons/garage.png',
  };
  irrigation: CardSettings = {
    title: 'Arrosage automatique',
    iconClass: 'nb-coffee-maker',
    type: 'warning',
    src: 'assets/icons/irrigation-system.png',
  };

  statusCards: string;

  commonStatusCardsSet: CardSettings[] = [
    this.mainDoor,
    this.rollerShadesCard,
    this.garage,
    this.irrigation,
  ];

  statusCardsByThemes: {
    default: CardSettings[];
    cosmic: CardSettings[];
    corporate: CardSettings[];
    dark: CardSettings[];
  } = {
    default: this.commonStatusCardsSet,
    cosmic: this.commonStatusCardsSet,
    corporate: [
      {
        ...this.mainDoor,
        type: 'warning',
      },
      {
        ...this.rollerShadesCard,
        type: 'primary',
      },
      {
        ...this.garage,
        type: 'danger',
      },
      {
        ...this.irrigation,
        type: 'info',
      },
    ],
    dark: this.commonStatusCardsSet,
  };

  constructor(private themeService: NbThemeService,
              private solarService: SolarData) {
    this.themeService.getJsTheme()
      .pipe(takeWhile(() => this.alive))
      .subscribe(theme => {
        this.statusCards = this.statusCardsByThemes[theme.name];
    });

    this.solarService.getSolarData()
      .pipe(takeWhile(() => this.alive))
      .subscribe((data) => {
        this.solarValue = data;
      });
  }

  

  ngOnDestroy() {
    this.alive = false;
  }
}
