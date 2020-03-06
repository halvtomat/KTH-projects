import React, { Component } from "react";
import "./MenuItem.css";

class MenuItem extends Component {
  constructor(props) {
    super(props);
  }

  render() {
      console.log("creating menuitem");
    return ( 
        <div className="MenuItem">
            <div className="dishName">{this.props.dish.title}</div>
            <div className="dishPrice">SEK: {this.props.dish.price}</div>
        </div>     
    );
  }
}

export default MenuItem;
