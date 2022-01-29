<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">


  <h3 align="center">ASTERIX Decoder</h3>

  <p align="center">
    A multiplatform software for decoding categories 10, 19, 20 and 21 of the EUROCONTROL ASTERIX Protocol
    <br />
    <br />
    <br />
    ·
    <a href="https://github.com/AntonioAlarcon32/Asterix_Decoder/issues">Report Bug</a>
    ·
    <a href="https://github.com/AntonioAlarcon32/Asterix_Decoder/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![main_image][product-screenshot]](https://github.com/AntonioAlarcon32/Asterix_Decoder/blob/main/images/normal_map.png)

This project has been developed as final bachelor's thesis at [EETAC](https://eetac.upc.edu/en). The software is capable of decoding the categories 10, 19, 20 and 21 of ASTERIX protocol. It is also capable of showing all the info about a single packet, show info of de ASTERIX file or simulate the time of the file and show the targets in a map. You can also connect to multicast emitters and receive the info in this software, showing the targets in a map and saving the file for later processing

### Features

* Decoding of ASTERIX (Cat 10,19,20 and 21 v2.1)
* Info about single packets.
* See all packets of a emitter during time, showing the trajectory of the target in the detected categories
* Info about the file.
* Time simulations, showing targets in a map.
* Packet filtering with callsign, address, mode 3/a, track number or category.
* File exporting to KML or CSV.
* Multicast receiving of the protocol.

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

This project has been built using Qt frameworkwith QMake, Qt Widgets and QML. It uses OpenStreetMap as map provider.

* [Qt](https://www.qt.io/)
* [QMake](https://doc.qt.io/qt-5/qmake-manual.html)
* [OpenStreetMap](https://www.openstreetmap.org/#map=6/40.007/-2.488)

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Antonio Alarcón - [LinkedIn](https://www.linkedin.com/in/antonio-alarcon-garcia-saavedra/) - antonio.alarcon@estudiantat.upc.edu

Project Link: [https://github.com/AntonioAlarcon32/Asterix_Decoder](https://github.com/AntonioAlarcon32/Asterix_Decoder)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Qt Framework](https://www.qt.io/)
* [OpenStreetMap](https://www.openstreetmap.org/#map=6/40.007/-2.488)
* [Stack Overflow](https://stackoverflow.com/)
* [EUROCONTROL ASTERIX](https://www.eurocontrol.int/asterix)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/AntonioAlarcon32/Asterix_Decoder.svg?style=for-the-badge
[contributors-url]: https://github.com/AntonioAlarcon32/Asterix_Decoder/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/AntonioAlarcon32/Asterix_Decoder.svg?style=for-the-badge
[forks-url]: https://github.com/AntonioAlarcon32/Asterix_Decoder/network/members
[stars-shield]: https://img.shields.io/github/stars/AntonioAlarcon32/Asterix_Decoder.svg?style=for-the-badge
[stars-url]: https://github.com/AntonioAlarcon32/Asterix_Decoder/stargazers
[issues-shield]: https://img.shields.io/github/issues/AntonioAlarcon32/Asterix_Decoder.svg?style=for-the-badge
[issues-url]: https://github.com/AntonioAlarcon32/Asterix_Decoder/issues
[license-shield]: https://img.shields.io/github/license/AntonioAlarcon32/Asterix_Decoder.svg?style=for-the-badge
[license-url]: https://github.com/AntonioAlarcon32/Asterix_Decoder/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/antonio-alarcon-garcia-saavedra/
[product-screenshot]: images/normal_map.png