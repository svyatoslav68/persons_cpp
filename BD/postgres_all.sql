--
-- PostgreSQL database cluster dump
--

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS;
CREATE ROLE slava;
ALTER ROLE slava WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN NOREPLICATION NOBYPASSRLS PASSWORD 'SCRAM-SHA-256$4096:HNI1mP/GffHBTaWNECHHQQ==$Z29jn1Oo20Q0lo5f7KNZ8F+ic8862NuzuCA0b50If/E=:7YxvRmEMHuSKhnxq5P2VaMy07Nd3zxvT7i/SNs6ugRg=';






--
-- Databases
--

--
-- Database "template1" dump
--

\connect template1

--
-- PostgreSQL database dump
--

-- Dumped from database version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- PostgreSQL database dump complete
--

--
-- Database "postgres" dump
--

\connect postgres

--
-- PostgreSQL database dump
--

-- Dumped from database version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- PostgreSQL database dump complete
--

--
-- Database "test" dump
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: test; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE test WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE = 'ru_RU.UTF-8';


ALTER DATABASE test OWNER TO postgres;

\connect test

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: soci_json_test; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.soci_json_test (
    data json
);


ALTER TABLE public.soci_json_test OWNER TO slava;

--
-- Name: ten; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.ten (
    id smallint,
    value_int smallint
);


ALTER TABLE public.ten OWNER TO slava;

--
-- Name: 16754; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('16754');


ALTER LARGE OBJECT 16754 OWNER TO slava;

--
-- Name: 16758; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('16758');


ALTER LARGE OBJECT 16758 OWNER TO slava;

--
-- Name: 17197; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('17197');


ALTER LARGE OBJECT 17197 OWNER TO slava;

--
-- Name: 17201; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('17201');


ALTER LARGE OBJECT 17201 OWNER TO slava;

--
-- Name: 17642; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('17642');


ALTER LARGE OBJECT 17642 OWNER TO slava;

--
-- Name: 17646; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('17646');


ALTER LARGE OBJECT 17646 OWNER TO slava;

--
-- Name: 18085; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('18085');


ALTER LARGE OBJECT 18085 OWNER TO slava;

--
-- Name: 18089; Type: BLOB; Schema: -; Owner: slava
--

SELECT pg_catalog.lo_create('18089');


ALTER LARGE OBJECT 18089 OWNER TO slava;

--
-- Data for Name: soci_json_test; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.soci_json_test (data) FROM stdin;
{"tool":"soci","result":42}
\.


--
-- Data for Name: ten; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.ten (id, value_int) FROM stdin;
1	1
2	2
3	3
4	4
5	5
6	6
7	7
8	8
9	9
10	10
\.


--
-- Data for Name: BLOBS; Type: BLOBS; Schema: -; Owner: -
--

BEGIN;

SELECT pg_catalog.lo_open('16754', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('16758', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('17197', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('17201', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('17642', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('17646', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('18085', 131072);
SELECT pg_catalog.lo_close(0);

SELECT pg_catalog.lo_open('18089', 131072);
SELECT pg_catalog.lo_close(0);

COMMIT;

--
-- Name: DATABASE test; Type: ACL; Schema: -; Owner: postgres
--

GRANT ALL ON DATABASE test TO slava;


--
-- PostgreSQL database dump complete
--

--
-- Database "units" dump
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: units; Type: DATABASE; Schema: -; Owner: slava
--

CREATE DATABASE units WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE = 'ru_RU.UTF-8';


ALTER DATABASE units OWNER TO slava;

\connect units

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: t_visualization; Type: TYPE; Schema: public; Owner: slava
--

CREATE TYPE public.t_visualization AS ENUM (
    'before',
    'after',
    'none'
);


ALTER TYPE public.t_visualization OWNER TO slava;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: persons; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.persons (
    idperson integer NOT NULL,
    family text NOT NULL,
    name text NOT NULL,
    parent text NOT NULL,
    current_unit integer DEFAULT '-1'::integer NOT NULL,
    last_units integer[]
);


ALTER TABLE public.persons OWNER TO slava;

--
-- Name: persons_idperson_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.persons_idperson_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.persons_idperson_seq OWNER TO slava;

--
-- Name: persons_idperson_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.persons_idperson_seq OWNED BY public.persons.idperson;


--
-- Name: units; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.units (
    idunit integer NOT NULL,
    number integer NOT NULL,
    name text DEFAULT ''::text NOT NULL,
    parent integer DEFAULT '-1'::integer NOT NULL,
    type text DEFAULT ''::text NOT NULL,
    visualization public.t_visualization
);


ALTER TABLE public.units OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.units_idunit_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.units_idunit_seq OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.units_idunit_seq OWNED BY public.units.idunit;


--
-- Name: persons idperson; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.persons ALTER COLUMN idperson SET DEFAULT nextval('public.persons_idperson_seq'::regclass);


--
-- Name: units idunit; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.units ALTER COLUMN idunit SET DEFAULT nextval('public.units_idunit_seq'::regclass);


--
-- Data for Name: persons; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.persons (idperson, family, name, parent, current_unit, last_units) FROM stdin;
1	Воронин	Святослав	Петрович	-1	\N
2	Лабунец	Артем	Владимирович	-1	\N
\.


--
-- Data for Name: units; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.units (idunit, number, name, parent, type, visualization) FROM stdin;
0	-1	ФСО	-1	ведомство	none
1	-1	Спецсвязь	0	служба	none
2	-1	СБП	0	служба	none
3	-1	УНТО	1	управление	none
4	-1	УЭССС	1	управление	none
5	-1	УШДС	1	управление	none
6	-1	секретариат	0	секретариат	none
7	-1	секретариат	1	секретариат	none
8	-1	секретариат	3	секретариат	none
9	-1	секретариат	4	секретариат	none
10	-1	секретариат	5	секретариат	none
11	-1	кадров	3	группа	before
12	-1	кадров	4	отделение	before
13	1		3	отдел	after
14	2		3	отдел	after
15	3		3	отдел	after
16	4		3	отдел	after
17	5		3	отдел	after
18	6		3	отдел	after
19	1		4	отдел	after
20	2		4	отдел	after
21	3		4	отдел	after
22	4		4	отдел	after
23	5		4	отдел	after
24	6		4	отдел	after
25	7		4	отдел	after
26	8		4	отдел	after
27	9		4	отдел	after
28	1		5	отдел	after
29	2		5	отдел	after
30	4		5	отдел	after
31	5		5	отдел	after
32	6		5	отдел	after
33	1		14	отделение	after
34	2		14	отделение	after
35	1		24	отделение	after
36	2		24	отделение	after
37	4		24	отделение	after
38	3		24	группа	after
39	1		27	отделение	after
40	2		27	отделение	after
\.


--
-- Name: persons_idperson_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.persons_idperson_seq', 2, true);


--
-- Name: units_idunit_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.units_idunit_seq', 40, true);


--
-- PostgreSQL database dump complete
--

--
-- PostgreSQL database cluster dump complete
--

