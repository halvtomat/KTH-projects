import React, { Component } from "react";
import { Link } from "react-router-dom";
import "./Welcome.css";

class Welcome extends Component {
  render() {
    return (
      <div className="Welcome">
        <p className="Text">{lorem}</p>

        <Link to="/search" className="SearchLink">
          <button className="button" id="start">Start planning</button>
        </Link>
      </div>
    );
  }
}
const lorem = "Lorem ipsum dolor sit, amet consectetur adipisicing elit.Distinctio deserunt, corporis laborum, mollitia accusamusipsum nesciunt quibusdam sapiente natus veniam voluptassequi sed! Voluptate reprehenderit hic quis voluptas,reiciendis ducimus exercitationem quia mollitia fugiat,quaerat molestiae aperiam neque consequatur quos.";

export default Welcome;
