import React, { Component } from "react";
import "./Details.css";

class Details extends Component {
    constructor(props) {
        super(props);
    }

    componentDidMount() {
        this.props.model.addObserver(this);
    }
    componentWillUnmount() {
        this.props.model.removeObserver(this);
    }

    render() {
        return (
        <div className="Details">
        </div>
        );
    }
}

export default Details;
