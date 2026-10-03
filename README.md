# Engine Prototype — SDL3

## Onderzoeksvraag

Kan de voorgestelde `IRenderer`-abstractie (Adapter/Facade) met SDL3
geïmplementeerd worden om twee gekleurde objecten te renderen én kan SDL3's
eigen audio-API (zonder losse SDL3_mixer-dependency) gebruikt worden voor een
fire-and-forget geluidseffect?

Dit is de SDL3-helft van de in het onderzoeksdocument voorgestelde
vergelijking; de SDL2-tegenhanger moet nog gebouwd worden voordat er een
definitieve keuze gemaakt kan worden (zie "Status" hieronder).

## Bevindingen

- De `IRenderer`-interface liet zich zonder gedoe implementeren met SDL3:
  geen enkel SDL-type lekt buiten `SDL3Renderer`, `Window` en `AudioPlayer`.
- SDL3's `SDL_CreateRenderer` heeft geen driver-index-argument meer (anders
  dan SDL2) — `nullptr` volstaat om de beste backend te laten kiezen.
- Rendering gebruikt `SDL_FRect` (floats) in plaats van SDL2's `SDL_Rect`
  (ints); dit vereist een expliciete cast bij het doorgeven van de
  x/y/breedte/hoogte-parameters.
- Geluid afspelen kon zonder SDL3_mixer: `SDL_LoadWAV` +
  `SDL_OpenAudioDeviceStream` + `SDL_PutAudioStreamData` is voldoende voor
  fire-and-forget SFX. Dit schakelt een hele extra vcpkg-dependency uit
  t.o.v. de SDL2-route (die wél `SDL2_mixer` nodig heeft voor hetzelfde
  resultaat) — een concreet verschil om mee te nemen in de vergelijking.
- Geen noemenswaardige performance-verrassingen bij twee simpele
  rechthoeken; met een target van "zo goed mogelijk" (geen hard getal) is
  hier verder niets gemeten.

**Status:** geen go/no-go nog — dat volgt pas na de SDL2-prototype volgens
dezelfde scope (zie onderzoeksdocument, sectie 6-7), zodat beide eerlijk op
dezelfde criteria vergeleken worden.

---

Minimale prototype die valideert of de voorgestelde `IRenderer`-architectuur
(zie onderzoeksdocument) werkt met SDL3: twee gekleurde rechthoeken renderen
en een geluidseffect afspelen via SDL3's eigen audio-stream-API.

## Build

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Voor het eerste gebruik

Zet een `.wav`-bestand op `assets/sounds/blip.wav` (map bestaat al, alleen
een voorbeeldgeluid toevoegen). Zonder dit bestand draait de prototype nog
gewoon door — alleen het geluid faalt dan stil met een foutmelding in de
console.

## Besturing

- **Esc / venster sluiten** — stopt het programma (via `SDL_EVENT_QUIT`).
- **Spatiebalk** — speelt `assets/sounds/blip.wav` af.

## Structuur

| Bestand | Rol |
|---|---|
| `main.cpp` | Init → loop → shutdown, bevat verder geen SDL-logica. |
| `Engine.*` | Orkestreert Window, IRenderer en AudioPlayer; verwerkt input en rendert elk frame. |
| `Window.*` | Wrapt het SDL3-venster. |
| `IRenderer.h` | Het Adapter/Facade-contract — enige interface die `Engine` kent. |
| `SDL3Renderer.*` | Concrete SDL3-implementatie van `IRenderer`. |
| `AudioPlayer.*` | Laadt en speelt een `.wav` af via `SDL_AudioStream` (geen aparte SDL3_mixer-dependency nodig). |

Dit dekt de minimale scope uit sectie 6 van het onderzoeksdocument. Voor de
vergelijking met SDL2 bouw je dezelfde klassen met een `SDL2Renderer` en een
SDL2-variant van `AudioPlayer` (die dan wél `SDL_mixer` als aparte vcpkg-
dependency nodig heeft).
